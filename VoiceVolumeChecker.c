def quiet_speaking_advice(speaking_volume):
    if speaking_volume > 70:
        return "Your speaking volume is too high! Please speak more quietly."
    elif speaking_volume > 50:
        return "Try lowering your voice a bit."
    else:
        return "Good! You are speaking at the perfect volume."

# Example: Input user's speaking volume
user_volume = int(input("Enter speaking volume (0-100): "))
advice = quiet_speaking_advice(user_volume)
print(advice)
