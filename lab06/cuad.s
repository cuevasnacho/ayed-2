	// parametros

	movz x10,0xFF,lsl 16
	mov x2,120 // altura
	mov x1,100 // ancho
	mov x0,x20 // guardo la posicion inicial del arreglo
	mov x3,30 // x
	mov x4,50 // y	
	
	bl cuad // salta a cuad y guarda en x30 la direccion del PC+1

cuad:
	mov x9,640
	mul x4,x4,x9 // 640 y
	add x4,x4,x3 // x + 640 y
	lsl x0,x4,2 // obtengo la direccion donde comienza el cuad
	lsl x9,x9,2 // multiplico 640x4 para saltar de fila
	mov x10,x0 // guardo la direccion en otro registro

l1:
	mov x11,x1 // renuevo el ancho
	add x10,x10,x9 // salto a la siguiente linea
l0:
	stur w10,[x0,#0] // pinto el pixel
	add x0,x0,4 // avanzo el puntero al siguiente pixel
	sub x11,x11,1 // decremento el ancho
	cbnz x11,l0 // si no es cero, sigue iterando
	sub x2,x2,1 // decremento la altura
	cbnz x2,l1 // si no es cero, pasa a la siguiente fila

br x30
