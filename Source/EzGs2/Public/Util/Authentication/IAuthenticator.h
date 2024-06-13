#pragma once
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Util
{
    class EZGS2_API IAuthenticator
    {
    public:
        virtual ~IAuthenticator() = default;

        virtual Gs2::Core::Model::FGs2ErrorPtr Authentication(
            const Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            const FString UserId,
            const FString Password,
            const TSharedPtr<Gs2::Auth::Model::FAccessTokenPtr> Result
        ) = 0;

        virtual bool NeedReAuthentication() = 0;
    };
    typedef TSharedPtr<IAuthenticator> IAuthenticatorPtr;
}
