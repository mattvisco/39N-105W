uniform sampler2DRect tex1;
uniform sampler2DRect tex2;

void main (void){
    
    vec2 pos = gl_TexCoord[0].st;
    
    vec4 txt1 = texture2DRect(tex1, pos);
    vec4 txt2 = texture2DRect(tex2, pos);
    
//    gl_FragColor = vec4(1,0,0,1);
    gl_FragColor = txt1 + txt2;// + txt2;//txt1;// + txt2;
}
