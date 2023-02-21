#pragma once

#include "Core/Net/Rest/Gs2RestSession.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"

namespace Gs2::UE5::Util
{
    class EZGS2_API IReOpener
    {
    public:
        virtual ~IReOpener() = default;

        virtual void SetAuthenticator(
            const IAuthenticatorPtr Authenticator,
            const FString UserId,
            const FString Password,
            Auth::Model::FEzAccessTokenPtr AccessToken
        ) = 0;
        
        virtual Gs2::Core::Model::FGs2ErrorPtr ReOpen(
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession,
            const Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr WebSocketSession
        ) = 0;
    };
    typedef TSharedPtr<IReOpener> IReOpenerPtr;
}
