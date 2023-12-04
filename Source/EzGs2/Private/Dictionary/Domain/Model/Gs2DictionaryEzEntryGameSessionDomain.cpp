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
 *
 * deny overwrite
 */

#include "Dictionary/Domain/Model/Gs2DictionaryEzEntryGameSessionDomain.h"

namespace Gs2::UE5::Dictionary::Domain::Model
{

    TOptional<FString> FEzEntryGameSessionDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzEntryGameSessionDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzEntryGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzEntryGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzEntryGameSessionDomain::EntryName() const
    {
        return Domain->EntryName;
    }

    FEzEntryGameSessionDomain::FEzEntryGameSessionDomain(
        Gs2::Dictionary::Domain::Model::FEntryAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzEntryGameSessionDomain::FGetEntryWithSignatureTask::FGetEntryWithSignatureTask(
        TSharedPtr<FEzEntryGameSessionDomain> Self,
        TOptional<FString> KeyId
    ): Self(Self), KeyId(KeyId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzEntryGameSessionDomain::FGetEntryWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Dictionary::Domain::Model::FEzEntryGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->GetWithSignature(
                    MakeShared<Gs2::Dictionary::Request::FGetEntryWithSignatureRequest>()
                        ->WithEntryModelName(Self->EntryName())
                        ->WithKeyId(KeyId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Dictionary::Domain::Model::FEzEntryGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
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

    TSharedPtr<FAsyncTask<FEzEntryGameSessionDomain::FGetEntryWithSignatureTask>> FEzEntryGameSessionDomain::GetEntryWithSignature(
        TOptional<FString> KeyId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetEntryWithSignatureTask>>(
            this->AsShared(),
            KeyId
        );
    }

    FEzEntryGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzEntryGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzEntryGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Dictionary::Model::FEzEntryPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Dictionary::Model::FEzEntry::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzEntryGameSessionDomain::FModelTask>> FEzEntryGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzEntryGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Dictionary::Model::FEzEntryPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Dictionary::Model::FEntryPtr Item)
            {
                Callback(Gs2::UE5::Dictionary::Model::FEzEntry::FromModel(Item));
            }
        );
    }

    void FEzEntryGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
