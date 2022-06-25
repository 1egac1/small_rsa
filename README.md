# Implemintation of RSA in C language
This is implementation of RSA in C language. Exemple of using the library you can find in ` test.c ` file. To сompile the library, computer must have ` gmp `.
## Generating keys ##
To generate the keys you must to create var of type ` rsa_keys_t `. To generate keys you must use fuction:
``` 
rsa_keys_t rsa_keys_t_variable;

mpz_generate_rsa_keys(&rsa_keys_t_variable);
``` 

## Text ecryption/decryption ##
### Unsigned int encryption/decription ###
To encrypt ` unsigned int ` variable you must to use functon:
```
mpz_rsa_enrypt_ui(rsa_keys_t *keys, unsigned int data, mpz_t output);
```
Cipher text will be saved in ` mpz_t ` variable ` output `.
To decrypt ` unsigned int ` variable you must to use function
```
mpz_rsa_decrypt_ui(rsa_keys_t *keys, mpz_t input, unsigned int *output);
```
In ` output ` we will get source text.
# Реализация RSA на языке C
Данная реализация асимметричного шифрования RSA использует библиотеку ` gmp ` для работы с большими числами и генерации простых чисел.
## Генерация ключей ##
Сначала необходимо создать структуру типа ` rsa_keys_t `. Затем, чтобы сгенерировать ключи воспользуйтесь функцией
```
rsa_keys_t rsa_keys_t_variable;

mpz_generate_rsa_keys(&rsa_keys_t_variable);
```
## Шифорование/расшифровка текста ##
### Шифорование/расшивровка переменных типа unsigned int ###
Чтобы зашифровать переменную типа ` unsigned int ` воспользуйтесь следующей ф-цией:
```
// ...
// ключи сгенерированы выше
mpz_t output;
mpz_init(output); // переменная куда будет сохраняться зашифрованный текст
unsigned int data = 12345 // текст, который необходимо зашифровать 

mpz_rsa_enrypt_ui(&keys, data, output); // функция, отвечающая за шифрование
```
Чтобы расшифровать данные, сохранённые в переменню ` output ` выше, воспользуемся следующей функцией:
```
unsigned int output_ui; // переменная для вывода расшифрованного текста

mpz_rsa_decrypt_ui(&keys, output, &output_ui); // первой передаётся структура данных, содержащая ключи, 
			//второй зашифрованные данные, 
			//третьей указатель на переменную для вывода теста
```
