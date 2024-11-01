from langchain.chat_models import ChatOpenAI # importing the chat model
from langchain.prompts import PromptTemplate # for creating chat templates
from langchain.memory import ConversationSummaryBufferMemory # to store and rreply based in temporary user based convo
from langchain.chains import ConversationChain # for chaining user queries and models and memory stored


with open("api_key.txt", "r") as jammer:
    api_key = jammer.read()

# model name
llm_model = "gpt-3.5-turbo"

# having this as a global variable, reducing the necessity of reloading the model on and on and on
chat_model = ChatOpenAI(temperature=0.6, model=llm_model, openai_api_key="sk-vjrBcaQxxxxxxxxxxxxx") # make it semi-creative, so temp is kinda low

# memory to keep track on convo between human and AI - 
memory = ConversationSummaryBufferMemory(llm=chat_model, max_token_limit=100)
# creating a chain to store convos between user and AI, in memory and reply based on it
conversation = ConversationChain( 
    llm=chat_model, memory = memory, verbose=False # this is just a combination of memory - model - prompt
)
# ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' #

chat_prompt = """
System: You are an Medical/Healtcare expert, who resolve user queries on\
        healthcare and medical related problems.

reply to user queries delimited by triple backticks

IMPORTANT:
    -> Have normal conversations
    -> be friendly to humans and greet them
    -> resolve queries with responses in simple english
    -> if user queries are out from healthcare and medicines\
       reply "Can't help you with it, Please Stick to asking queries from my domain"
    -> restrict the response within 40-70 words, reply as informative as possible
    -> prescribe medicinal exercises, drugs and other treaments too

user query: ```{query}```
"""

# prompt template for above prompt
chat_template = PromptTemplate.from_template(chat_prompt)

# ''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' #

def doTempalte(template, **variables) -> str:
    '''
    kwargs -> variables
    ensure exact variables in give in template is fed
    else an error message will be displayed
    '''
    
    return template.format(**variables)



def get_completion(prompt):

    ai_response = conversation.predict(input=prompt)

    return ai_response # returning the response from llm

# '''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''' #
def mainCall(query):
    # feeding in template, getting respone, summarizing and storing it in memory
    return get_completion(doTempalte(chat_template, query=query))


if __name__ == "__main__":
    
    
    # x = input("Please enter your query: ")
    # print("\n")
    # while x!="stall":
    #     print("AI:", get_completion(doTempalte(chat_template, query=x)), end="\n\n----------------------------------------------------------\n\n")
    #     x = input("User: ")
    #     print("\n")    
    ...

    print(mainCall("What is important for our body"))