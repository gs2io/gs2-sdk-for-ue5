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

#include "Auth/Domain/Model/Gs2AuthEzAccessTokenDomain.h"

namespace Gs2::UE5::Auth::Domain::Model
{

    TOptional<FString> FEzAccessTokenDomain::Token() const
    {
        return Domain->Token;
    }

    TOptional<FString> FEzAccessTokenDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<int64> FEzAccessTokenDomain::Expire() const
    {
        return Domain->Expire;
    }

    TOptional<FString> FEzAccessTokenDomain::Status() const
    {
        return Domain->Status;
    }

    FEzAccessTokenDomain::FEzAccessTokenDomain(
        Gs2::Auth::Domain::Model::FAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzAccessTokenDomain::FLoginTask::FLoginTask(
        TSharedPtr<FEzAccessTokenDomain> Self,
        FString Body,
        FString Signature,
        TOptional<FString> KeyId
    ): Self(Self), Body(Body), Signature(Signature), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAccessTokenDomain::FLoginTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Auth::Domain::Model::FEzAccessTokenDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FLoginTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->LoginBySignature(
                    MakeShared<Gs2::Auth::Request::FLoginBySignatureRequest>()
                        ->WithKeyId(KeyId)
                        ->WithBody(Body)
                        ->WithSignature(Signature)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Auth::Domain::Model::FEzAccessTokenDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzAccessTokenDomain::FLoginTask>> FEzAccessTokenDomain::Login(
        FString Body,
        FString Signature,
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FLoginTask>>(
            this->AsShared(),
            Body,
            Signature,
            KeyId
        );
    }

    FEzAccessTokenDomain::FModelTask::FModelTask(
        TSharedPtr<FEzAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAccessTokenDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Auth::Model::FEzAccessTokenPtr> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Auth::Model::FEzAccessToken::FromModel(Task->GetTask().Result());
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzAccessTokenDomain::FModelTask>> FEzAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzAccessTokenDomain::Subscribe(TFunction<void(Gs2::UE5::Auth::Model::FEzAccessTokenPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Auth::Model::FAccessTokenPtr Item)
            {
                Callback(Gs2::UE5::Auth::Model::FEzAccessToken::FromModel(Item));
            }
        );
    }

    void FEzAccessTokenDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
