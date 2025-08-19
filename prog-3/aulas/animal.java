public class 
    public abstract class animal {
     protected String nome, cor;
     protected double peso;
     protected int idade, altura;

     public animal(String nome, String cor, double peso, int idade, int altura){
        super();
        this.nome=nome;
        this.cor=cor;
        this.peso=peso;
        this.idade=idade;
        this.altura=altura;
     }
     public String getNome(){
        return nome;
     }
     public void setNome(String nome){
        this.nome=nome;
     }

     public String getCor(){
        return cor;
     }
     public void setCor(String cor){
        this.cor=cor;
     }

     public double getPeso(){
        return peso;
     }
     public void setPeso(double peso){
        this.peso=peso;
     }

     public int getIdade(){
        return idade;
     }
     public void setIdade(int idade){
        this.idade=idade;
     }

     public int getAltura(){
        return altura ;
     }
     public void setAltura(int altura){
        this.altura=altura;
     }
     public void comer(){};


     public void dormir(){};


     public abstract void soar ();

        
    }

    public class cachorro {
        public String tamanhoRabo; 
        public cachorro(String nome, String cor, double peso, int idade, int altura){
            super(nome, cor, peso, idade, altura);
        }

    }

