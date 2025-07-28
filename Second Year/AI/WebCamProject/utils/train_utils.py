import numpy as np
from PIL import Image
import os
import glob

from sklearn.neighbors import KNeighborsClassifier

from utils.face_utils import extract_face_embedding


def load_dataset(data_path="data"):
    embeddings = []
    labels = []

    for label in os.listdir(data_path):
        label_path = os.path.join(data_path, label)
        if not os.path.isdir(label_path):
            continue
        for image_path in glob.glob(os.path.join(label_path, "*.jpg")):
            try:
                img = Image.open(image_path).convert("RGB")  # ✅ FIXED
                emb = extract_face_embedding(img)
                if emb is not None:
                    embeddings.append(emb)
                    labels.append(label)
            except Exception as e:
                print(f"Skipping {image_path}: {e}")
                continue

    return np.array(embeddings), np.array(labels)


def train_classifier(embeddings, labels):
    knn = KNeighborsClassifier(n_neighbors=1)
    knn.fit(embeddings, labels)
    return knn
