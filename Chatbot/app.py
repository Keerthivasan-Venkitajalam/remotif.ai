from flask import Flask, request, jsonify, render_template
from flask_restful import Api, Resource
from langchain_community.vectorstores import Chroma
from langchain_community.embeddings import OpenAIEmbeddings
from langchain_openai import OpenAI
from langchain.chains import RetrievalQA
import os
import logging
from dotenv import load_dotenv

load_dotenv()

os.environ['OPENAI_API_KEY'] = os.getenv('OPENAI_API_KEY')

app = Flask(__name__)
api = Api(app)

embeddings = OpenAIEmbeddings()
vectorstore = Chroma(persist_directory="./chroma_db", embedding_function=embeddings)

llm = OpenAI(temperature=0)

qa_chain = RetrievalQA.from_chain_type(
    llm=llm,
    chain_type="stuff",
    retriever=vectorstore.as_retriever(search_kwargs={"k": 5}),
    return_source_documents=True
)

class ChatbotAPI(Resource):
    def __init__(self):
        self.greetings = ['hi', 'hello', 'hey', 'greetings', 'howdy','wassup']
        self.farewells = ['bye', 'goodbye', 'see you', 'farewell','thanks','thank you']

    def is_greeting(self, text):
        return any(text.lower().startswith(word) for word in self.greetings)

    def is_farewell(self, text):
        return any(word in text.lower().split() for word in self.farewells)

    def post(self):
        try:
            data = request.get_json()
            question = data.get('question', '').strip()
            
            if not question:
                return jsonify({"error": "No question provided"}), 400

            if self.is_greeting(question):
                return jsonify({"answer": "Hello! How can I assist you today? Feel free to ask about programming courses or career advice for developers."})

            if self.is_farewell(question):
                return jsonify({"answer": "Goodbye! If you have any more questions about programming courses or development careers in the future, don't hesitate to ask."})

            result = qa_chain({"query": question})
            
            if len(result['result']) < 20 or "I don't know" in result['result'].lower():
                return jsonify({
                    "answer": "I apologize, but I don't have enough specific information to answer that question confidently. However, I can offer some general advice or suggestions. Could you provide more details about what you're looking for, or ask a related question?"
                })

            return jsonify({"answer": result['result']})

        except Exception as e:
            logging.error(f"Error processing request: {str(e)}")
            return jsonify({"error": "An error occurred while processing your request. Please try again or rephrase your question."})

api.add_resource(ChatbotAPI, '/api/chat')

@app.route('/')
def home():
    return render_template('index.html')

if __name__ == '__main__':
    app.run(debug=True)
