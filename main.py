import pickle

with open('data_0.pkl', 'rb') as f:
    data = pickle.load(f)
    print(data)