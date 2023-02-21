#pragma once
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Core/Net/Rest/Gs2RestSession.h"

namespace Gs2::UE5::Util
{
    class EZGS2_API IAuthenticator
    {
    public:
        virtual ~IAuthenticator() = default;

        virtual Gs2::Core::Model::FGs2ErrorPtr Authentication(
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr RestSession,
            const FString UserId,
            const FString Password,
            const TSharedPtr<Gs2::UE5::Auth::Model::FEzAccessTokenPtr> Result
        ) = 0;
    };
    typedef TSharedPtr<IAuthenticator> IAuthenticatorPtr;
}
