public class Aluno{
    String nome;
    double peso;
    double altura;
    String sexo;

    Aluno(String nome, double peso, double altura, String sexo){
        this.nome=nome;
        this.peso=peso;
        this.altura=altura;
        this.sexo=sexo;
    }

    void imprimir(){
        double imc = this.peso/(this.altura*this.altura);

        System.out.println("nome:"+this.nome +"\n altura:"+ this.altura+ "\npeso:" + this.peso + "\nsexo"+ this.sexo + "\n imc:" + imc );

    }


}