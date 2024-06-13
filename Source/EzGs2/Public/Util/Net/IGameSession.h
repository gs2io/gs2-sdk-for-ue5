#pragma once
#include "Auth/Model/Gs2AuthEzAccessToken.h"

namespace Gs2::UE5::Util
{
    class EZGS2_API IGameSession
    {
    public:
        FString UserId;
        Gs2::Auth::Model::FAccessTokenPtr AccessTokenValue;

        virtual ~IGameSession() = default;
        
        virtual Gs2::Auth::Model::FAccessTokenPtr AccessToken() = 0;

    };
    typedef TSharedPtr<IGameSession> IGameSessionPtr;
}
