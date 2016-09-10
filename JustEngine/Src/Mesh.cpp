#include "pch.h"
#include "Mesh.h"
#include "Buffer.h"

#include <vector>
#include "..\Include\Mesh.h"

namespace JustEngine
{
	std::shared_ptr<Mesh> Mesh::Create(const std::string& name)
	{
		return std::make_shared< Mesh >(name);
	}

	Mesh::Mesh(const std::string& name):IdxBuffer("vertex_index", D3D11_USAGE_DEFAULT, D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER),
		PositionBuffer("vertex_position", D3D11_USAGE_DEFAULT, D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER),
		ColorBuffer("vertex_color", D3D11_USAGE_DEFAULT, D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER)
	{
	
	}

	void Mesh::SetupBuffers(UINT * idxData, UINT idxCount, Vector3 * posData, UINT posCount, Vector4 * colorData, UINT colorCount)
	{
		IdxBuffer.Data = idxData;
		IdxBuffer.DataCount = idxCount;

		PositionBuffer.Data = posData;
		PositionBuffer.DataCount = posCount;

		ColorBuffer.Data = colorData;
		ColorBuffer.DataCount = colorCount;

		UpdateBuffer();
	}

	void Mesh::UpdateBuffer()
	{
		IdxBuffer.UpdateBuffer();

		std::vector<Buffer*> buffers{ &PositionBuffer, &ColorBuffer };
		int buffSize = buffers.size();
		ppBuffers = new ID3D11Buffer*[ buffSize ];
		pStrides = new UINT[ buffSize ];
		pOffsets = new UINT[ buffSize ];
		BufferSize = 0;
		for each (auto pbuff in buffers)
		{
			if (pbuff->UpdateBuffer()) {
				ppBuffers[ BufferSize ] = static_cast<ID3D11Buffer*>(pbuff->GetBuffer());
				pStrides[ BufferSize ] = pbuff->GetStride();
				pOffsets[ BufferSize ] = pbuff->GetOffset();

				BufferSize++;
			}
		}
	}

	bool Mesh::BindDraw(ID3D11DeviceContext* context)
	{
		context->IASetVertexBuffers(0, BufferSize, ppBuffers, pStrides, pOffsets);
		context->IASetIndexBuffer(IdxBuffer.pBuffer, DXGI_FORMAT_R32_UINT, 0);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		context->DrawIndexed(IdxBuffer.DataCount, 0, 0);

		return true;
	}
}