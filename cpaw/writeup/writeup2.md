[misc]image

unzip misc100.zip
cat mimetype
open misc100.zip with libreOffive

[reversing]

strings rev100 |grep -A cpaw

[forensic]

string misc100 |grep lovelive -> hoge.txt

```python3
with open("hoge.txt", "r") as f:
  data = f.read()
print(data.replace("lovelive!", "")
```
[Crypto]
gcc crypto100.c
./a.out ruoYced_ehpigniriks_i_llrg_stae 

[network] can you login?

wireshirk network100.pcap
---look for ftp

---ubuntu
ftp 152.7.52.186
login
ftp> passive
ftp> ls -a
ftp> get .hidden_flag_file
ftp> quit

[Web] redirect

use BurpSuite

---firefox
proxy settings: http- localhost:8080
---burpsuite
set intercept_mode

enter url& check response headers on buipsuite
