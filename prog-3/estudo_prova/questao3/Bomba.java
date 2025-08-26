public class Bomba{
    String tipo;
    double preco;
    double litro;

    Bomba(String tipo, double preco, double litro){
        this.tipo = tipo;
        this.preco = preco;
        this.litro = litro;
    }

    void abValor(double valor ){
        double resultado = valor/this.preco;
        if(resultado<=this.litro){
            this.litro= this.litro-resultado;
            System.out.printf("vc abasteceu: %.2f\n", resultado,"L");
        }else 
        System.out.println("nao tem combustivel suficiente");

    }

    void abLitro(double litro){
        double resultado= litro*this.preco;
        if(litro<=this.litro){
            this.litro= this.litro-litro;
            System.out.printf("valor: %.2f\n", resultado);
        }else 
        System.out.println("nao tem combustivel");

    }

    void alValor(double novoV){
        this.preco=novoV;
        System.out.println("novo valo:" + this.preco);

    }

    void alLitro(double novoL){
        this.litro= novoL;
        System.out.println("nova quantidade"+ this.litro);

    }

    void abcombo(double abastecer){
        this.litro+=abastecer;
        System.out.println("total combustivel:" + this.litro);
    }
}