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
 20;
 -52.35316;121.90276;-40.89385;,
 54.13449;121.90276;-40.89385;,
 78.67479;60.43030;-60.40310;,
 -76.89334;60.43030;-60.40310;,
 54.13449;121.90276;-40.89385;,
 54.13449;121.90276;43.76284;,
 78.67479;60.43030;63.27205;,
 78.67479;60.43030;-60.40310;,
 -52.35316;121.90276;43.76284;,
 -76.89334;60.43030;63.27205;,
 -52.35316;121.90276;-40.89385;,
 -76.89334;60.43030;-60.40310;,
 -65.06845;0.67250;-49.91207;,
 -91.18271;71.61602;-77.02683;,
 90.39731;71.61602;-77.02621;,
 64.28378;0.67250;-49.91207;,
 90.39733;71.61611;76.67444;,
 64.28381;0.67250;51.13565;,
 -91.18267;71.61611;76.67520;,
 -65.06841;0.67250;51.13574;;
 
 11;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;5,8,9,6;,
 4;8,10,11,9;,
 4;8,5,4,10;,
 4;12,13,14,15;,
 4;15,14,16,17;,
 4;17,16,18,19;,
 4;19,18,13,12;,
 4;19,12,15,17;,
 4;13,18,16,14;;
 
 MeshMaterialList {
  4;
  11;
  0,
  2,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Boss_face.png";
   }
  }
  Material {
   0.800000;0.498824;0.367059;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.778039;0.363922;0.181961;1.000000;;
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
  11;
  0.000000;0.302497;-0.953150;,
  0.928730;0.370757;0.000000;,
  0.000000;0.302497;0.953150;,
  -0.928731;0.370755;0.000000;,
  0.000000;1.000000;0.000000;,
  0.000002;-0.357011;-0.934100;,
  0.938444;-0.345431;-0.000000;,
  0.000002;-0.338713;0.940890;,
  -0.938441;-0.345439;0.000000;,
  0.000000;-1.000000;-0.000000;,
  -0.000000;1.000000;-0.000001;;
  11;
  4;0,0,0,0;,
  4;1,1,1,1;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;4,4,4,4;,
  4;5,5,5,5;,
  4;6,6,6,6;,
  4;7,7,7,7;,
  4;8,8,8,8;,
  4;9,9,9,9;,
  4;10,10,10,10;;
 }
 MeshTextureCoords {
  20;
  0.077587;0.000000;,
  0.900821;0.000000;,
  1.090537;1.000000;,
  -0.112128;1.000000;,
  1.001694;-0.935967;,
  1.001694;-0.935967;,
  1.230999;0.517665;,
  1.230999;0.517665;,
  0.006671;-0.935967;,
  -0.222633;0.517665;,
  0.006671;-0.935967;,
  -0.222633;0.517665;,
  0.076011;1.972107;,
  -0.091853;0.818037;,
  1.075353;0.818037;,
  0.907494;1.972107;,
  1.075353;0.818035;,
  0.907494;1.972107;,
  -0.091853;0.818035;,
  0.076011;1.972107;;
 }
}
