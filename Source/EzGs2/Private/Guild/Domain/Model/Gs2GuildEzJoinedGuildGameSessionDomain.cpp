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

#include "Guild/Domain/Model/Gs2GuildEzJoinedGuildGameSessionDomain.h"

#include "Guild/Domain/Model/Gs2GuildEzGuildGameSessionDomain.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    TOptional<FString> FEzJoinedGuildGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzJoinedGuildGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzJoinedGuildGameSessionDomain::GuildModelName() const
    {
        return Domain->GuildModelName;
    }

    TOptional<FString> FEzJoinedGuildGameSessionDomain::GuildName() const
    {
        return Domain->GuildName;
    }

    FEzJoinedGuildGameSessionDomain::FEzJoinedGuildGameSessionDomain(
        Gs2::Guild::Domain::Model::FJoinedGuildAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzJoinedGuildGameSessionDomain::FUpdateMemberMetadataTask::FUpdateMemberMetadataTask(
        TSharedPtr<FEzJoinedGuildGameSessionDomain> Self,
        TOptional<FString> Metadata
    ): Self(Self), Metadata(Metadata)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzJoinedGuildGameSessionDomain::FUpdateMemberMetadataTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->UpdateMemberMetadata(
                    MakeShared<Gs2::Guild::Request::FUpdateMemberMetadataRequest>()
                        ->WithMetadata(Metadata)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzJoinedGuildGameSessionDomain::FUpdateMemberMetadataTask>> FEzJoinedGuildGameSessionDomain::UpdateMemberMetadata(
        TOptional<FString> Metadata
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateMemberMetadataTask>>(
            this->AsShared(),
            Metadata
        );
    }

    FEzJoinedGuildGameSessionDomain::FWithdrawGuildTask::FWithdrawGuildTask(
        TSharedPtr<FEzJoinedGuildGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzJoinedGuildGameSessionDomain::FWithdrawGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzJoinedGuildGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Withdrawal(
                    MakeShared<Gs2::Guild::Request::FWithdrawalRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Guild::Domain::Model::FEzJoinedGuildGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzJoinedGuildGameSessionDomain::FWithdrawGuildTask>> FEzJoinedGuildGameSessionDomain::WithdrawGuild(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FWithdrawGuildTask>>(
            this->AsShared()
        );
    }

    FEzJoinedGuildGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzJoinedGuildGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzJoinedGuildGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Guild::Model::FEzJoinedGuildPtr> Result
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
                *Result = Gs2::UE5::Guild::Model::FEzJoinedGuild::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzJoinedGuildGameSessionDomain::FModelTask>> FEzJoinedGuildGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzJoinedGuildGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzJoinedGuildPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Guild::Model::FJoinedGuildPtr Item)
            {
                Callback(Gs2::UE5::Guild::Model::FEzJoinedGuild::FromModel(Item));
            }
        );
    }

    void FEzJoinedGuildGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
