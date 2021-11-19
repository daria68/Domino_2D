
// Shader-ul de fragment / Fragment shader  
 
 #version 400

in vec4 ex_Color;
out vec4 out_Color;
uniform int codCol;

void main(void)
  {

	switch(codCol){
		
		case 6:
		   out_Color=vec4 (0.0, 0.0, 0.0, 0.0);
		   break;
		case 5:
		   out_Color=vec4 (0.0, 0.0, 0.5, 0.0);
		   break;
		case 4:
		   out_Color=vec4 (0.0, 0.0, 0.8, 0.0);
		   break;
		case 3:
		   out_Color=vec4 (0.0, 0.1, 0.9, 0.0);
		   break;
		case 2:
		   out_Color=vec4 (0.0, 0.4, 0.9, 0.0);
		   break;
		case 1:
		   out_Color=vec4 (0.0, 0.5, 1.0, 0.0);
		   break;
		
		case 7:
		   out_Color=vec4 (0.4, 0.2, 0.2, 0.0);
		   break;
		case 8:
			out_Color=vec4 (0.0, 0.0, 0.0, 0.0);
		    break;
		case 9:
			out_Color=vec4 (0.0, 0.8, 0.9, 0.0);
		    break;

		case 10:
		   out_Color=vec4 (0.6, 0.2, 0.3, 0.0);
		   break;
		default:
		   out_Color = ex_Color;
	

	}

  }
 