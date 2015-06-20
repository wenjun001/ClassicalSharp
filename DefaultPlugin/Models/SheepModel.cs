﻿using System;
using ClassicalSharp;
using ClassicalSharp.GraphicsAPI;
using ClassicalSharp.Model;
using ClassicalSharp.Renderers;

namespace DefaultPlugin {

	public class SheepModel : IModel {
		
		public bool Fur = true;
		int furTextureId;
		
		public SheepModel( Game window ) : base( window ) {
			vertices = new VertexPos3fTex2f[partVertices * 6 * ( Fur ? 2 : 1 )];
			Head = MakeHead();
			Torso = MakeTorso();
			LeftLegFront = MakeLeg( -0.3125f, -0.0625f, -0.4375f, -0.1875f );
			RightLegFront = MakeLeg( 0.0625f, 0.3125f, -0.4375f, -0.1875f );
			LeftLegBack = MakeLeg( -0.3125f, -0.0625f, 0.3125f, 0.5625f );
			RightLegBack = MakeLeg( 0.0625f, 0.3125f, 0.3125f, 0.5625f );
			if( Fur ) {
				FurHead = MakeFurHead();
				FurTorso = MakeFurTorso();
				FurLeftLegFront = MakeFurLeg( -0.34375f, -0.03125f, -0.46875f, -0.15625f );
				FurRightLegFront = MakeFurLeg( 0.03125f, 0.34375f, -0.46875f, -0.15625f );
				FurLeftLegBack = MakeFurLeg( -0.34375f, -0.03125f, 0.28125f, 0.59375f );
				FurRightLegBack = MakeFurLeg( 0.03125f, 0.34375f, 0.28125f, 0.59375f );
			}
			
			vb = graphics.InitVb( vertices, VertexPos3fTex2f.Size );
			vertices = null;
			DefaultTexId = graphics.LoadTexture( "sheep.png" );
			furTextureId = graphics.LoadTexture( "sheep_fur.png" );
		}
		
		ModelPart MakeHead() {
			return MakePart( 0, 0, 8, 6, 6, 8, 6, 6, -0.1875f, 0.1875f, 1f, 1.375f, -0.875f, -0.375f, false );
		}
		
		ModelPart MakeTorso() {
			return MakeRotatedPart( 28, 8, 6, 16, 8, 6, 8, 16, -0.25f, 0.25f, 0.75f, 1.125f, -0.5f, 0.5f, false );
		}
		
		ModelPart MakeFurHead() {
			return MakePart( 0, 0, 6, 6, 6, 6, 6, 6, -0.21875f, 0.21875f, 0.96875f, 1.40625f, -0.78125f, -0.34375f, false );
		}
		
		ModelPart MakeFurTorso() {
			return MakeRotatedPart( 28, 8, 6, 16, 8, 6, 8, 16, -0.375f, 0.375f, 0.65625f, 1.21875f, -0.625f, 0.625f, false );
		}
		
		ModelPart MakeLeg( float x1, float x2, float z1, float z2 ) {
			return MakePart( 0, 16, 4, 12, 4, 4, 4, 12, x1, x2, 0f, 0.75f, z1, z2, false );
		}
		
		ModelPart MakeFurLeg( float x1, float x2, float z1, float z2 ) {
			return MakePart( 0, 16, 4, 6, 4, 4, 4, 6, x1, x2, 0.34375f, 0.78125f, z1, z2, false );
		}
		
		public override string ModelName {
			get { return "sheep"; }
		}
		
		public override float NameYOffset {
			get { return Fur ? 1.48125f: 1.075f; }
		}
		
		protected override void DrawPlayerModel( Player player, PlayerRenderer renderer ) {
			int texId = renderer.MobTextureId <= 0 ? DefaultTexId : renderer.MobTextureId;
			graphics.Bind2DTexture( texId );
			
			DrawRotate( 0, 1.125f, -0.5f, -pitch, 0, 0, Head );
			DrawPart( Torso );
			DrawRotate( 0, 0.75f, -0.3125f, leftLegXRot, 0, 0, LeftLegFront );
			DrawRotate( 0, 0.75f, -0.3125f, rightLegXRot, 0, 0, RightLegFront );
			DrawRotate( 0, 0.75f, 0.4375f, rightLegXRot, 0, 0, LeftLegBack );
			DrawRotate( 0, 0.75f, 0.4375f, leftLegXRot, 0, 0, RightLegBack );

			if( Fur ) {
				graphics.Bind2DTexture( furTextureId );
				DrawPart( FurTorso );
				DrawRotate( 0, 1.125f, -0.5f, -pitch, 0, 0, FurHead );
				DrawRotate( 0, 0.75f, -0.3125f, leftLegXRot, 0, 0, FurLeftLegFront );
				DrawRotate( 0, 0.75f, -0.3125f, rightLegXRot, 0, 0, FurRightLegFront );
				DrawRotate( 0, 0.75f, 0.4375f, rightLegXRot, 0, 0, FurLeftLegBack );
				DrawRotate( 0, 0.75f, 0.4375f, leftLegXRot, 0, 0, FurRightLegBack );
			}
		}
		
		public override void Dispose() {
			graphics.DeleteVb( vb );
			graphics.DeleteTexture( ref DefaultTexId );
			if( Fur ) {
				graphics.DeleteTexture( ref furTextureId );
			}
		}
		
		ModelPart Head, Torso, LeftLegFront, RightLegFront, LeftLegBack, RightLegBack;
		ModelPart FurHead, FurTorso, FurLeftLegFront, FurRightLegFront,
			FurLeftLegBack, FurRightLegBack;
	}
}