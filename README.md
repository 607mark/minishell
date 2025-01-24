# **Minishell**  
*"As beautiful as a shell"*  
created by - [Anttoni](https://github.com/manttoni) and [Mark](https://github.com/607mark)  
---

You can add a **Credits** or **Authors** section to your README to include this information. Here's an example:  

---

## **Credits**  
Minishell was created with ❤️ by:  


---

This format is clean, and it ensures proper attribution. You can adjust the heading style or wording as you prefer!

## **Overview**  
Minishell is a simple, lightweight Unix shell built from scratch. It replicates the basic functionality of Bash, offering:  
- Command execution  
- Environment variable management
- Piping
- Input/output redirection  
- Heredoc support  
- Graceful signal handling
- Robust error handling

### **Installation**  
Clone the repository:  
```bash
git clone https://github.com/your-username/minishell.git
cd minishell
make
```

Run the shell:  
```bash
./minishell
```

---

### **Usage**  

## **Built-in Commands**  

Minishell implements the following built-in commands, mimicking their behavior in Bash:  

| **Command** | **Description** | **Example** |  
|-------------|-----------------|-------------|  
| `echo`      | Prints text to the terminal. Supports the `-n` option to omit the trailing newline. | `echo -n "Hello, World!"` |  
| `cd`        | Changes the current directory. Accepts relative or absolute paths. | `cd /home/user` |  
| `pwd`       | Prints the current working directory. No options are supported. | `pwd` |  
| `export`    | Sets environment variables. No options are supported. | `export VAR=value` |  
| `unset`     | Removes environment variables. No options are supported. | `unset VAR` |  
| `env`       | Displays all environment variables. No arguments or options are supported. | `env` |  
| `exit`      | Exits the shell with an optional status code. | `exit 0` |  

Each built-in is implemented to provide basic functionality and adhere to the specified constraints.  

- **Commands**: minishell can execute any command that is located in the directories specified in your $PATH
- **Pipes**: Combine commands using `|`  
- **Redirections**: Input (`<`), Output (`>`), Append (`>>`), Heredoc (`<<`)  

Example:  
```bash
echo "Hello, World!" | grep "World" > output.txt
```

### **Environment Variables**  
```bash
export VAR=value
echo $VAR
```

### **Heredoc Example**  
```bash
cat << EOF
This is a heredoc example.
EOF
```

---

## **License**  
This project is licensed under the [MIT License](LICENSE).  

---
