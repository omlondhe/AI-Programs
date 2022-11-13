import speech_recognition as sr
import pyaudio

r = sr.Recognizer()
	
while (1):
	try:
		with sr.Microphone() as source:
			print("Speak...")
			r.adjust_for_ambient_noise(source, duration=0.2)
			audio = r.listen(source)
			text = r.recognize_google(audio)
			text = text.lower()

			print(f"You said: {text}")
			
	except sr.RequestError as e:
		print("Could not request results; {0}".format(e))
		
	except sr.UnknownValueError as ue:
		print(f"unknown error occurred {ue}")
