# A bash-like shell program


* Written in C
* Takes user input, parses it and executes given commands
  * Handles pipes
  * Handles redirections ``>``, ``>>``, ``<`` and ``<<`` (heredoc)
  * Handles built-in commands:
    * ``pwd``, ``echo``, ``cd``, ``exit``, ``unset`` and ``export``
   
## Test it yourself

- Currently most compatible with linux because of usage of GNU readline (especially for rl_clear_history()).
- To make it work with macOS for example, some adjustments are needed:

  ```
   #include <readline/history.h>

  change rl_clear_history() to clear_history();
  ```

#### - run ``make``
#### - run the executable ``minishell``

![preview](https://github.com/JiggyStardust/minishell/blob/main/minishell.gif)

#### - use it like your regular bash:

<img width="700" height="425" alt="image" src="https://github.com/user-attachments/assets/cfea3a04-0bdb-4ec6-94fa-cd2147cff76a" />


