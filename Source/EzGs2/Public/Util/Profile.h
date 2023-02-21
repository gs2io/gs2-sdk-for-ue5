/*
* Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#pragma once

#include "CoreMinimal.h"
#include "IAuthenticator.h"
#include "IReOpener.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Core/Model/Region.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"

namespace Gs2::UE5::Core::Domain
{
    class FGs2Domain;
}

namespace Gs2::UE5::Util
{
    class EZGS2_API FProfile:
        public TSharedFromThis<FProfile>
    {
        FString ClientId;
        FString ClientSecret;
        Gs2::Core::Model::ERegion Region;

        IReOpenerPtr ReOpener;
        IAuthenticatorPtr AuthenticatorValue;
        FString UserIdValue;
        FString PasswordValue;
        
    public:
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Gs2RestSession;
        Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr Gs2WebSocketSession;
        TOptional<FString> DistributorNamespaceName;
        
        FProfile(
            FString ClientId,
            FString ClientSecret,
            Gs2::Core::Model::ERegion Region,
            IReOpenerPtr ReOpener,
            TOptional<FString> DistributorNamespaceName = TOptional<FString>()
        );
        
        class FInitializeTask final :
            public Gs2::Core::Util::TGs2Future<Core::Domain::FGs2Domain>,
            public TSharedFromThis<FInitializeTask>
        {
            TSharedPtr<FProfile> Self;

        public:
            explicit FInitializeTask(
                TSharedPtr<FProfile> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Core::Domain::FGs2Domain>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FInitializeTask>> Initialize();
        
        class FReConnectTask final :
            public Gs2::Core::Util::TGs2Future<void>,
            public TSharedFromThis<FReConnectTask>
        {
            TSharedPtr<FProfile> Self;

        public:
            explicit FReConnectTask(
                TSharedPtr<FProfile> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FReConnectTask>> ReConnect();

        class FLoginTask final :
            public Gs2::Core::Util::TGs2Future<Auth::Model::FEzAccessToken>,
            public TSharedFromThis<FLoginTask>
        {
            TSharedPtr<FProfile> Self;
            FString UserId;
            FString Password;

        public:
            explicit FLoginTask(
                const TSharedPtr<FProfile> Self,
                const FString UserId,
                const FString Password
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Auth::Model::FEzAccessToken>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FLoginTask>> Login(
            const IAuthenticatorPtr Authenticator,
            const FString UserId,
            const FString Password
        );

        template <class T>
        class FRunTask final :
            public Gs2::Core::Util::TGs2Future<void>,
            public TSharedFromThis<FRunTask<T>>
        {
            TSharedPtr<FProfile> Profile;
            TFunction<Gs2::Core::Model::FGs2ErrorPtr ()> Func;
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken;

            bool Retry;

        public:
            explicit FRunTask(
                TSharedPtr<FProfile> Profile,
                TFunction<Gs2::Core::Model::FGs2ErrorPtr ()> Func,
                Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
            ): Profile(Profile), Func(Func), AccessToken(AccessToken), Retry(false)
            {
                
            }

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void>> Result
            ) override
            {
                const auto Error = Func();
                if (Error != nullptr)
                {
                    if (Retry)
                    {
                        return Error;
                    }
                    if (Error->Type() == "SessionNotOpen")
                    {
                        const auto Future = Profile->ReConnect();
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            Future->EnsureCompletion();
                            return Future->GetTask().Error();
                        }
                        Future->EnsureCompletion();
                    }
                    if (Error->Type() == "Unauthorized")
                    {
                        if (Profile->AuthenticatorValue == nullptr)
                        {
                            return Error;
                        }
                        const auto Future = Profile->Login(
                            Profile->AuthenticatorValue,
                            Profile->UserIdValue,
                            Profile->PasswordValue
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            Future->EnsureCompletion();
                            return Future->GetTask().Error();
                        }
                        AccessToken
                            ->WithToken(Future->GetTask().Result()->GetToken())
                            ->WithExpire(Future->GetTask().Result()->GetExpire())
                            ->WithUserId(Future->GetTask().Result()->GetUserId());
                        Future->EnsureCompletion();
                    }
                    Retry = true;
                    return Action(Result);
                }
                return nullptr;
            }
        };

        template<class T>
        TSharedPtr<FAsyncTask<FRunTask<FAsyncTask<T>>>> Run(
            TFunction<Gs2::Core::Model::FGs2ErrorPtr ()> Func,
            Gs2::UE5::Auth::Model::FEzAccessTokenPtr AccessToken
        )
        {
            return Gs2::Core::Util::New<FAsyncTask<FRunTask<FAsyncTask<T>>>>(
                this->AsShared(),
                Func,
                AccessToken
            );
        }
        
        class FFinalizeTask final :
            public Gs2::Core::Util::TGs2Future<void>,
            public TSharedFromThis<FFinalizeTask>
        {
            TSharedPtr<FProfile> Self;

        public:
            explicit FFinalizeTask(
                TSharedPtr<FProfile> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void>> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FFinalizeTask>> Finalize();
    };
    typedef TSharedPtr<FProfile> FProfilePtr;
}
