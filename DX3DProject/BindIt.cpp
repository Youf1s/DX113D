#include "BindIt.h"

ID3D11Device* BindIt::GetDevice(Graphics& Gfx)
{
    return Gfx.pDevice.Get();
}

ID3D11DeviceContext* BindIt::GetContext(Graphics& Gfx)
{
    return Gfx.pContext.Get();
}
