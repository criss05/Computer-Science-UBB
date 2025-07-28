import cv2
import os
import argparse

def capture_images(label, out_dir="data", count=90):
    save_path = os.path.join(out_dir, label)
    os.makedirs(save_path, exist_ok=True)

    cap = cv2.VideoCapture(0)
    img_count = 0

    while img_count < count:
        ret, frame = cap.read()
        if not ret:
            break
        cv2.imshow(f"Capturing {label}", frame)
        key = cv2.waitKey(1)
        if key & 0xFF == ord('s'):
            file_path = os.path.join(save_path, f"{label}_{img_count}.jpg")
            cv2.imwrite(file_path, frame)
            print(f"Saved {file_path}")
            img_count += 1
        elif key & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--label", required=True, help="Label for the captured images (e.g., owner, pet)")
    args = parser.parse_args()
    capture_images(args.label)
