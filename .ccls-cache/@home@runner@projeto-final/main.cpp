/*
>Projeto Final<
Discentes: Iara Silva Neto e Henrique Menezes Oliveira
*/

#include <iostream>
#include <fstream>
using namespace std;

struct usuarios{
  string login, senha;
  int tipo;
};
struct livros{
  string nome, editor, autor;
};
struct emprestimo{
string nome, aluno;
};

//____________________login____________________

int login(){
  string senha, login;
  cout<<"\n===============================================\n";
  cout<<"Seja bem vindo(a), faça o Login para continuar!\n";
  cout<<"===============================================\n";
  cout<<"\nInforme o nome de usuário: ";
  cin>>login;
  cout<<"Informe a senha: ";
  cin>>senha;
  system("clear");
  string u, s;
  int permissao;
  ifstream arquivo("users.txt");
  bool logou=false;
  while(arquivo>>u>>s>>permissao){
    if(login==u && senha==s){
      return permissao;
    }
  }
  arquivo.close();
  cout<<"\nUsuário ou senha inválidos!"<<endl;
  return -1;
}

//____________________administrador____________________

//lista todos os usuários
void listaUsuario(){
  usuarios temp;
  cout<<"\n";
  ifstream arquivo("users.txt", ios::in);
  while(arquivo>>temp.login>>temp.senha>>temp.tipo){
    cout<<"- "<<temp.login<<endl;
  }
}
//cadastrar usuários
void cadastroUsuario(){
  usuarios temp;
  cout<<"Qual o nome do usuário? ";
  cin>>temp.login;
  cout<<"Qual a senha? ";
  cin>>temp.senha;
  cout<<"Qual a permissão? (1. Administrador; 2. Funcionário; 3. Aluno): ";
  cin>>temp.tipo;
  if(temp.tipo>3 || temp.tipo<1){
    cout<<"\nOpção impossível, tente novamente!\n";
  }
  else{
    ofstream arquivo("users.txt", ios::app);
    arquivo<<endl<<temp.login<<" "<<temp.senha<<" "<<temp.tipo;
    cout<<"\nUsuário cadastrado com sucesso!\n";
    arquivo.close();
  }
}

//editar usuários
void editarUsuario(){
  ifstream arquivo("users.txt");
  if(!arquivo.is_open()){
    cout<<"Falha ao abrir o arquivo!";
    return;
  }
  ofstream temp("temp.txt");
  string qual, novo;
  bool achou=false;
  int opcaoEdit;
  usuarios edit;
  cout<<"\nQual usuário deseja editar? ";
  cin>>qual;
  while(arquivo>>edit.login>>edit.senha>>edit.tipo){
    if(edit.login==qual){
      achou=true;
      cout<<"O que deseja alterar? (1.Login; 2. Senha; 3. Permissão): ";
      cin>>opcaoEdit;
      if(opcaoEdit==1){
        cout<<"Qual o novo login? ";
        cin>>novo;
        temp<<novo<<" "<<edit.senha<<" "<<edit.tipo<<endl;
        cout<<"\nAlteração bem sussedida!"<<endl;
      }
      if(opcaoEdit==2){
        cout<<"Qual a nova senha? ";
        cin>>novo;
        temp<<edit.login<<" "<<novo<<" "<<edit.tipo<<endl;
        cout<<"\nAlteração bem sussedida!"<<endl;
      }
      if(opcaoEdit==3){
        cout<<"Qual a nova permissão? ";
        cin>>novo;
        temp<<edit.login<<" "<<edit.senha<<" "<<novo<<endl;
        cout<<"\nAlteração bem sussedida!"<<endl;
      }
    }
    else{
      temp<<edit.login<<" "<<edit.senha<<" "<<edit.tipo<<endl;
    }
  }
  if(!achou){
    cout<<"\nUsuário não encontrado!"<<endl;
  }
  
  arquivo.close();
  temp.close();
  remove("users.txt");
  rename("temp.txt", "users.txt");
}

//excluir usuários
void excluirUsuario(){
  ifstream arquivo("users.txt");
  if(!arquivo.is_open()){
    cout<<"Falha ao abrir o arquivo!";
    return;
  }
  ofstream temp("temp.txt");
  string qual, novo;
  bool achou=false;
  int opcaoEdit;
  usuarios edit;
  cout<<"Qual usuário deseja excluir? ";
  cin>>qual;
  while(arquivo>>edit.login>>edit.senha>>edit.tipo){
    if(qual==edit.login){
      achou=true;
      cout<<"\nAlteração bem sussedida!"<<endl;
    }
    if(edit.login!=qual){
      temp<<edit.login<<" "<<edit.senha<<" "<<edit.tipo<<endl;
    }
  }
  if(!achou){
    cout<<"\nUsuário não encontrado!"<<endl;
  }
  arquivo.close();
  temp.close();
  remove("users.txt");
  rename("temp.txt", "users.txt");
}

//____________________funcionário____________________

//ver todos os livros cadastrados
void verLivros(){
  livros temp;
  bool achou=false;
  ifstream arquivo("livros.txt");
  cout<<"\n";
  while(arquivo >> temp.nome >> temp.editor >> temp.autor){
    cout<<" - "<<temp.nome<<endl;
    achou=true;
  }
  if(!achou){
    cout<<"Nenhum livro cadastrado!"<<endl;
  }
  arquivo.close();
}

//buscar livros
void buscarLivros(){
  livros temp;
  string qual;
  bool achou=false;
  cout<<"Qual livro deseja buscar? ";
  cin>>qual;
  cout<<"\n";
  ifstream arquivo("livros.txt");
  while(arquivo>>temp.nome>>temp.editor>>temp.autor){
    if(qual==temp.nome){
      cout<<"Nome: "<<temp.nome<<endl;
      cout<<"Editora: "<<temp.editor<<endl;
      cout<<"Autor: "<<temp.autor<<endl;
      achou=true;
      break;
    }
  }
  if(!achou){
    cout<<"Livro não encontrado!"<<endl;
  }
  arquivo.close();
}

//cadastrar, editar e excluir livros
void cadastroLivro(){
  livros temp;
  int op;
  do{
    cout << "\n1- Cadastrar livro" << endl;
    cout << "2- Editar livro" << endl;
    cout << "3- Excluir livro"<< endl;
    cout << "0- Voltar" << endl;
    cout << "Escolha uma opção: ";
    cin >> op;
    switch(op){
      case 1:{
        cout << "Qual o nome do livro que deseja cadastrar? ";
        cin >> temp.nome;
        cout << "Qual autor do livro? ";
        cin >> temp.autor;
        cout << "Qual editora do livro? ";
        cin >> temp.editor;
        ofstream arquivo("livros.txt", ios::app);
        arquivo<<endl<<temp.nome<<" "<<temp.autor<<" "<<temp.editor;
        arquivo.close(); 
        cout<<"\nLivro cadastrado com sucesso!"<<endl;
      break;}
      
      case 2:{
        ifstream arquivo("livros.txt");
        ofstream temp("temp.txt");
        string qual, novo;
        bool achou=false;
        int opcaoEdit;
        livros edit;
        cout<<"\nQual livro deseja editar? ";
        cin>>qual;
        while(arquivo>>edit.nome>>edit.autor>>edit.editor){
          if(edit.nome==qual){
            achou=true;
            cout<<"Qual informação deseja alterar (1.Nome do livro; 2. Autor; 3. Editora)? ";
            cin>>opcaoEdit;
            if(opcaoEdit==1){
              cout<<"Qual o novo nome do livro? ";
              cin>>novo;
              temp<<novo<<" "<<edit.autor<<" "<<edit.editor<<endl;
              cout<<"\nAlteração bem sussedida!"<<endl;
            }
            if(opcaoEdit==2){
              cout<<"Qual o novo autor do livro? ";
              cin>>novo;
              temp<<edit.nome<<" "<<novo<<" "<<edit.editor<<endl;
              cout<<"\nAlteração bem sussedida!"<<endl;
            }
            if(opcaoEdit==3){
              cout<<"Qual a nova editora do livro? ";
              cin>>novo;
              temp<<edit.nome<<" "<<edit.autor<<" "<<novo<<endl;
              cout<<"\nAlteração bem sussedida!"<<endl;
            }
          }
          else{
            temp<<edit.nome<<" "<<edit.autor<<" "<<edit.editor<<endl;
          }
        }
        if(!achou){
          cout<<"\nLivro não encontrado!"<<endl;
        }
        arquivo.close();
        temp.close();
        remove("livros.txt");
        rename("temp.txt", "livros.txt");
      break;}
      case 3:
        ifstream arquivo("livros.txt");
        if(!arquivo.is_open()){
          cout<<"Falha ao abrir o arquivo!";
          return;
        }
        ofstream temp("temp.txt");
        string qual, novo;
        bool achou=false;
        int opcaoEdit;
        livros edit;
        cout<<"Qual livro deseja excluir? ";
        cin>>qual;
        while(arquivo>>edit.nome>>edit.autor>>edit.editor){
          if(qual==edit.nome){
            achou=true;
            cout<<"\nLivro excluído com sucesso!"<<endl;
          }
          if(edit.nome!=qual){
            temp<<edit.nome<<" "<<edit.autor<<" "<<edit.editor<<endl;
          }
        }
        if(!achou){
          cout<<"\nLivro não encontrado!"<<endl;
        }
        arquivo.close();
        temp.close();
        remove("livros.txt");
        rename("temp.txt", "livros.txt");
      break;
    }
  }while(op!=0);
}

//ver todos os empréstimos de livros
void verEmprest(){
  emprestimo temp;
  bool achou=false;
  ifstream arquivo("emprestimo.txt");
  cout<<"\n";
  while(arquivo >> temp.nome >> temp.aluno){
    cout<<" - "<<temp.nome<<" - "<< temp.aluno<<endl;
    achou=true;
  }
  if(!achou){
    cout<<"Nenhum empréstimo de livro cadastrado!"<<endl;
  }
  arquivo.close();
}
//fazer empréstimos
void fazerEmprest(){
  emprestimo temp;
  cout << "Qual o nome do livro que deseja fazer empréstimo? "; 
  cin >> temp.nome;
  cout << "Para quem será o empréstimo? ";
  cin >> temp.aluno;
  
  ofstream arquivo("emprestimo.txt", ios::app);
        
  arquivo<<endl<<temp.nome<<" "<<temp.aluno;
        arquivo.close(); 
        cout<<"\nEmpréstimo bem sucedido!"<<endl;
  }


//____________________aluno____________________

//ver livros emprestados a mim
void verLivrosEmprestado(){
  emprestimo temp;
  string qual, save;
  bool achou=false;
  cout<<"\nQual seu nome? ";
  cin>>qual;
  cout<<"\n";
  ifstream arquivo("emprestimo.txt");
  while(arquivo>>temp.nome>>temp.aluno){
    if(qual==temp.aluno){
      cout<<"- "<<temp.nome<<endl;
      achou=true;
    }
  }
  if(!achou){
    cout<<"Nenhum livro foi emprestado a "<<qual<<"!"<<endl;
  }
  arquivo.close();
}

//____________________main____________________

int main(){
  string nome;
  int permissao, i;
  permissao=login();
  switch(permissao){
    //administrador
    case 1:
      int opcao;
      cout<<"Seja bem vindo(a)!"<<endl;
      do{
        cout<<"\n===Administrador===\n";
        cout<<"1. Listar usuários"<<endl;
        cout<<"2. Inserir usuários"<<endl;
        cout<<"3. Editar usuários"<<endl;
        cout<<"4. Excluir usuários"<<endl;
        cout<<"0. Sair"<<endl;
        cout<<"Escolha uma opção: ";
        cin>>opcao;
        switch(opcao){
          case 1:
            listaUsuario();
          break;
          case 2:
            cadastroUsuario();
          break;
          case 3:
            editarUsuario();
          break;
          case 4:
            excluirUsuario();
          break;
        }
      }while(opcao!=0);
    break;
    //funcionário
    case 2:
      cout<<"Seja bem vindo(a)!"<<endl;
      do{
        cout<<"\n===Funcionário===\n";
        cout<<"1. Ver livros cadastrados"<<endl;
        cout<<"2. Buscar um livro"<<endl;
        cout<<"3. Inserir, alterar ou excluir livro"<<endl;
        cout<<"4. Ver todos os empréstimos"<<endl;
        cout<<"5. Fazer empréstimo de livro"<<endl;
        cout<<"0. Sair"<<endl;
        cout<<"Escolha uma opção: ";
        cin>>opcao;
        switch(opcao){
          case 1:
            verLivros();
          break;
          case 2:
            buscarLivros();
          break;
          case 3:
            cadastroLivro();
          break;
          case 4:
            verEmprest();
          break;
          case 5:
            fazerEmprest();
          break;
        }
      }while(opcao!=0);
    break;
    //aluno
    case 3:
      cout<<"Seja bem vindo(a)!"<<endl;
      do{
        cout<<"\n===Aluno===\n";
        cout<<"1. Ver livros cadastrados"<<endl;
        cout<<"2. Buscar um livro"<<endl;
        cout<<"3. Ver livros emprestados a mim"<<endl;
        cout<<"0. Sair"<<endl;
        cout<<"Escolha uma opção: ";
        cin>>opcao;
        switch(opcao){
          case 1:
            verLivros();
          break;
          case 2:
            buscarLivros();
          break;
          case 3:
            verLivrosEmprestado();
          break;
        }
      }while(opcao!=0);
    break;    
  }
	main();
}