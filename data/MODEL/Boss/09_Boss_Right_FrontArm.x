xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 15;
 -136.78584;-6.19406;12.64746;,
 -20.54277;-10.61844;26.28726;,
 -19.47589;15.54937;29.74419;,
 -136.69392;24.94869;13.58493;,
 -18.18065;43.58111;-1.50787;,
 -135.63140;41.53363;-10.47088;,
 -14.43426;23.86672;-33.49597;,
 -134.66116;26.97581;-35.46390;,
 -15.44679;-8.59732;-36.69785;,
 -134.75230;-4.16706;-36.40115;,
 -19.34878;-26.76914;-4.15587;,
 -135.81470;-20.75199;-12.34554;,
 -20.54277;-10.61844;26.28726;,
 -136.78584;-6.19406;12.64746;,
 0.06803;-0.10389;-0.18349;;
 
 16;
 4;0,1,2,3;,
 4;3,2,4,5;,
 4;5,4,6,7;,
 4;7,6,8,9;,
 4;9,8,10,11;,
 4;11,10,12,13;,
 3;1,14,2;,
 3;2,14,4;,
 3;4,14,6;,
 3;6,14,8;,
 3;8,14,10;,
 3;10,14,12;,
 3;9,11,7;,
 3;7,11,5;,
 3;11,13,5;,
 3;5,13,3;;
 
 MeshMaterialList {
  2;
  16;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.645333;0.138039;0.020706;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  23;
  -0.121127;-0.538519;0.833862;,
  -0.099029;0.401580;0.910454;,
  -0.044919;0.785592;0.617112;,
  0.020392;0.521225;-0.853176;,
  0.009157;0.064111;-0.997901;,
  -0.018107;-0.848039;-0.529624;,
  0.214713;-0.631848;0.744760;,
  0.600109;-0.783995;-0.158813;,
  0.989285;-0.096817;0.109279;,
  0.026936;0.858444;-0.512200;,
  0.444134;-0.791781;-0.419318;,
  -0.083865;-0.872219;0.481873;,
  0.804934;-0.109850;0.583108;,
  0.860348;0.133905;0.491803;,
  0.914320;0.385687;0.123551;,
  0.942845;0.199844;-0.266657;,
  0.919472;0.010086;-0.393026;,
  -0.999140;0.004165;-0.041255;,
  -0.999140;0.004176;-0.041245;,
  -0.999141;0.004173;-0.041239;,
  -0.999141;0.004185;-0.041241;,
  -0.999140;0.004186;-0.041251;,
  -0.999140;0.004190;-0.041242;;
  16;
  4;0,6,1,1;,
  4;1,1,2,2;,
  4;9,9,3,3;,
  4;3,3,4,4;,
  4;5,10,7,5;,
  4;11,11,6,0;,
  3;12,8,13;,
  3;13,8,14;,
  3;14,8,15;,
  3;15,8,16;,
  3;10,8,7;,
  3;7,8,6;,
  3;17,18,19;,
  3;19,18,20;,
  3;18,21,20;,
  3;20,21,22;;
 }
 MeshTextureCoords {
  15;
  0.000000;0.250000;,
  0.000000;0.500000;,
  0.166670;0.500000;,
  0.166670;0.250000;,
  0.333330;0.500000;,
  0.333330;0.250000;,
  0.500000;0.500000;,
  0.500000;0.250000;,
  0.666670;0.500000;,
  0.666670;0.250000;,
  0.833330;0.500000;,
  0.833330;0.250000;,
  1.000000;0.500000;,
  1.000000;0.250000;,
  0.500000;0.865380;;
 }
}
