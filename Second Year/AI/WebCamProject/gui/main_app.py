import cv2
from tkinter import Tk, Label, Button, messagebox
from PIL import Image, ImageTk
from sympy.printing.pytorch import torch

from utils.face_utils import mtcnn, facenet
from utils.train_utils import load_dataset, train_classifier
from utils.video_utils import cv2_to_pil, draw_label_box

def launch_app():
    App(Tk()).root.mainloop()

class App:
    def __init__(self, root):
        self.cap = None
        self.root = root
        self.root.title("AI Webcam Classifier")
        self.running = False

        self.label = Label(root, text="Real-Time Classifier", font=("Helvetica", 16))
        self.label.pack()

        self.video_label = Label(root)
        self.video_label.pack()

        self.start_button = Button(root, text="Start", command=self.start)
        self.start_button.pack(pady=5)

        self.stop_button = Button(root, text="Stop", command=self.stop)
        self.stop_button.pack(pady=5)

        self.quit_button = Button(root, text="Quit", command=self.root.quit)
        self.quit_button.pack(pady=5)

        self.embeddings, self.labels = load_dataset()
        self.knn = train_classifier(self.embeddings, self.labels)

    def start(self):
        consent = messagebox.askyesno("Consent", "Use your webcam to detect you, your pet, or others. Continue?")
        if not consent:
            return
        self.cap = cv2.VideoCapture(0)
        self.running = True
        self.update_frame()

    def stop(self):
        self.running = False
        if hasattr(self, 'cap'):
            self.cap.release()
        self.video_label.config(image='')

    def update_frame(self):
        if self.running:
            ret, frame = self.cap.read()
            if not ret:
                return
            pil_img = cv2_to_pil(frame)
            boxes, _ = mtcnn.detect(pil_img)

            label = "Nobody"
            if boxes is not None:
                for box in boxes:
                    face = pil_img.crop(box).convert("RGB")
                    emb = mtcnn(face)
                    if emb is not None:
                        with torch.no_grad():
                            pred = self.knn.predict(facenet(emb.unsqueeze(0)).detach().cpu().numpy())[0]
                        draw_label_box(frame, box, pred)
                        label = pred
                    else:
                        draw_label_box(frame, box, "Unknown")
            else:
                cv2.putText(frame, label, (10, 30), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 0, 255), 2)

            img_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            imgtk = ImageTk.PhotoImage(image=Image.fromarray(img_rgb))
            self.video_label.imgtk = imgtk
            self.video_label.configure(image=imgtk)
            self.root.after(10, self.update_frame)
