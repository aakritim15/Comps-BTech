import threading
import time

class ReaderWriter:
    def __init__(self):
        self.readers = 0
        self.lock = threading.Lock()
        self.writing = threading.Semaphore(1)

    def start_read(self):
        with self.lock:
            # Wait for a writer to finish
            print(f"Reader {threading.current_thread().name} is waiting to read.")
            self.readers += 1
            if self.readers == 1:
                self.writing.acquire()  # First reader locks the writer

        print(f"Reader {threading.current_thread().name} is reading.")
        time.sleep(1)  # Simulate reading

    def end_read(self):
        with self.lock:
            self.readers -= 1
            if self.readers == 0:
                self.writing.release()  # Last reader unlocks the writer

    def start_write(self):
        print(f"Writer {threading.current_thread().name} is waiting to write.")
        self.writing.acquire()  # Wait for readers to finish

        print(f"Writer {threading.current_thread().name} is writing.")
        time.sleep(1)  # Simulate writing

    def end_write(self):
        self.writing.release()  # Release the writer lock

def reader(rw):
    rw.start_read()
    rw.end_read()

def writer(rw):
    rw.start_write()
    rw.end_write()

if __name__ == "__main__":
    rw = ReaderWriter()

    # Creating readers and writers
    threads = []
    for _ in range(10):
        t = threading.Thread(target=reader, args=(rw,))
        threads.append(t)
        t.start()

    for _ in range(2):
        t = threading.Thread(target=writer, args=(rw,))
        threads.append(t)
        t.start()

    # Wait for all threads to complete
    for t in threads:
        t.join()
