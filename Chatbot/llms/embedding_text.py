from PyPDF2 import PdfReader
from langchain.text_splitter import CharacterTextSplitter
from langchain.embeddings.openai import OpenAIEmbeddings
from langchain.vectorstores import FAISS
from langchain.chains.question_answering import load_qa_chain
from langchain.llms import OpenAI
from langchain.callbacks import get_openai_callback

import pickle

with open("api_key.txt", "r") as file:
    api_key = file.read()

def process_text(text): # returns knowledge base
    # Split the text into chunks using Langchain's CharacterTextSplitter
    text_splitter = CharacterTextSplitter(
        separator="\n",
        chunk_size=1000,
        chunk_overlap=200,
        length_function=len
    )
    chunks = text_splitter.split_text(text)
    
    # Convert the chunks of text into embeddings to form a knowledge base
    embeddings = OpenAIEmbeddings(api_key = api_key)
    knowledgeBase = FAISS.from_texts(chunks, embeddings)
    
    return knowledgeBase

def pdf_reader(path): # reads a pdf and extracts its text

    pdf_reader = PdfReader(path)
    # Text variable will store the pdf text
    text = ""
    for page in pdf_reader.pages:
        text += page.extract_text()
    
    return text

def return_similar_Chunk(knowledge_base, query): # retunrs a chunk that matches query from the knowledge base
    return knowledge_base.similarity_search(query, top_k=1)[0]


# """""""""""""""""""""""""""""

with open("medical_text/sample.txt", "r") as jammer:
    text = jammer.read()

k_base = process_text(text)

with open("vector_stores/general_practice_and_medicine_vector_store.pkl", 'wb') as jammer:
    pickle.dump(text, jammer)