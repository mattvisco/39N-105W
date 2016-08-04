uniform float imgTotal;
uniform bool focus;
uniform bool fading;
uniform sampler2DRect mask;
uniform sampler2DRect tex1;
uniform sampler2DRect tex2;
uniform sampler2DRect tex3;
uniform sampler2DRect tex4;
uniform sampler2DRect tex5;
uniform sampler2DRect tex6;
uniform sampler2DRect tex7;
uniform sampler2DRect tex8;
uniform sampler2DRect tex9;
uniform sampler2DRect tex10;
uniform sampler2DRect tex11;
uniform sampler2DRect tex12;
uniform sampler2DRect tex13;
uniform sampler2DRect tex14;
uniform sampler2DRect tex15;

void main (void){
    
    vec2 pos = gl_TexCoord[0].st;
    
    vec4 maskTex = texture2DRect(mask, pos);
    
    vec4 txt1 = texture2DRect(tex1, pos);
    vec4 txt2 = texture2DRect(tex2, pos);
    vec4 txt3 = texture2DRect(tex3, pos);
    vec4 txt4 = texture2DRect(tex4, pos);
    vec4 txt5 = texture2DRect(tex5, pos);
    vec4 txt6 = texture2DRect(tex6, pos);
    vec4 txt7 = texture2DRect(tex7, pos);
    vec4 txt8 = texture2DRect(tex8, pos);
    vec4 txt9 = texture2DRect(tex9, pos);
    vec4 txt10 = texture2DRect(tex10, pos);
    vec4 txt11 = texture2DRect(tex11, pos);
    vec4 txt12 = texture2DRect(tex12, pos);
    vec4 txt13 = texture2DRect(tex13, pos);
    vec4 txt14 = texture2DRect(tex14, pos);
    vec4 txt15 = texture2DRect(tex15, pos);
    
    vec4 color = vec4(0,0,0,1);
    float pct = 1.0 / imgTotal;
    
    color = mix(color, txt1, pct );
    color = mix(color, txt2, pct );
    color = mix(color, txt3, pct );
    color = mix(color, txt4, pct );
    color = mix(color, txt5, pct );
    color = mix(color, txt6, pct );
    color = mix(color, txt7, pct );
    color = mix(color, txt8, pct );
    color = mix(color, txt9, pct );
    color = mix(color, txt10, pct );
    color = mix(color, txt11, pct );
    color = mix(color, txt12, pct );
    color = mix(color, txt13, pct );
    color = mix(color, txt14, pct );
    color = mix(color, txt15, pct );
    
    gl_FragColor = color;
    
//    if(fading) {
//        float maskPct = maskTex.r;
//        float pct = 1.0 / imgTotal;
//        float pct1 = pct;
//        float pct15 = 0.0;
//        
//        
//        if(focus) {
//            pct1 = pct * (1.0-maskPct);
//            color = mix(color, txt15, pct );
//        } else {
//            pct15 = pct * maskPct;
//            color = mix(color, txt15, pct15 );
//        }
//        
//        color = mix(color, txt1, pct1 );
//        color = mix(color, txt2, pct );
//        color = mix(color, txt3, pct );
//        color = mix(color, txt4, pct );
//        color = mix(color, txt5, pct );
//        color = mix(color, txt6, pct );
//        color = mix(color, txt7, pct );
//        color = mix(color, txt8, pct );
//        color = mix(color, txt9, pct );
//        color = mix(color, txt10, pct );
//        color = mix(color, txt11, pct );
//        color = mix(color, txt12, pct );
//        color = mix(color, txt13, pct );
//        color = mix(color, txt14, pct );
//        
//        gl_FragColor = color;
//    } else {
//        float maskPct = maskTex.r;
//        float pct = (1.0 - maskTex.r) / (imgTotal - 1.0);
//        float pct1 = maskPct;
//        float pct2 = pct;
//        float pct3 = pct;
//        float pct4 = pct;
//        
//        // All pct are equal
//        if(maskPct <= 1.0/imgTotal) {
//            maskPct = 1.0 / imgTotal;
//            pct = maskPct;
//            pct1 = pct;
//            pct2 = pct;
//            pct3 = pct;
//            pct4 = pct;
//        } else {
//            // Interpolate based on maskPct
//            if(maskPct <= 0.25) {
//                pct1 = maskPct/4.0;
//                pct2 = pct1;
//                pct3 = pct1;
//                pct4 = pct1;
//            } else if(maskPct <= 0.5) {
//                float pctOver = (maskPct - 0.25) / 0.25; // 0 to 1 – at 1 pct3 gone, at 0 pct3 visible
//                pct1 = (maskPct / 4.0) * (1.0 - pctOver) + (maskPct / 3.0) * (pctOver);
//                pct2 = pct1;
//                pct3 = pct1;
//                pct4 = maskPct - (pct1 * 3.0);
//            } else if(maskPct <= 0.75) {
//                float pctOver = (maskPct - 0.5) / 0.25; // 0 to 1 – at 1 pct2 gone, at 0 pct2 visible
//                pct1 = ( (maskPct / 3.0) * (1.0-pctOver) ) + ( (maskPct/2.0) * pctOver );
//                pct2 = pct1;
//                pct3 = maskPct - (pct1 * 2.0);
//            } else {
//                float pctOver = (maskPct - 0.75) / 0.25; // 0 to 1 – at 1 pct2 gone, at 0 pct2 visible
//                pct1 = ( (maskPct / 2.0) * (1.0-pctOver) ) + (maskPct * pctOver);
//                pct2 = maskPct - pct1;
//            }
//        }
//
//
//        
//        if(focus) {
//            color = mix(color, txt1, pct1 );
//            color = mix(color, txt2, pct2 );
//            color = mix(color, txt3, pct3 );
//            color = mix(color, txt4, pct4 );
//        }else {
//            color = mix(color, txt1, pct );
//            color = mix(color, txt2, pct );
//            color = mix(color, txt3, pct );
//            color = mix(color, txt4, pct );
//        }
//        
//        color = mix(color, txt5, pct );
//        color = mix(color, txt6, pct );
//        color = mix(color, txt7, pct );
//        color = mix(color, txt8, pct );
//        color = mix(color, txt9, pct );
//        color = mix(color, txt10, pct );
//        color = mix(color, txt11, pct );
//        color = mix(color, txt12, pct );
//        color = mix(color, txt13, pct );
//        color = mix(color, txt14, pct );
//        if(focus) {
//            color = mix(color, txt15, pct );
//        } else {
//            color = mix(color, txt15, 0.0 );
//        }
//        
//        gl_FragColor = color;
//    }
}
