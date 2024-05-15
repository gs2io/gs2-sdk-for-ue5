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

#include "Guild/Domain/Model/Gs2GuildEzUserGameSessionDomain.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Guild::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzUserGameSessionDomain::FCreateGuildTask::FCreateGuildTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString GuildModelName,
        FString DisplayName,
        FString JoinPolicy,
        TOptional<int32> Attribute1,
        TOptional<int32> Attribute2,
        TOptional<int32> Attribute3,
        TOptional<int32> Attribute4,
        TOptional<int32> Attribute5,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles,
        TOptional<FString> GuildMemberDefaultRole
    ): Self(Self), GuildModelName(GuildModelName), DisplayName(DisplayName), JoinPolicy(JoinPolicy), Attribute1(Attribute1), Attribute2(Attribute2), Attribute3(Attribute3), Attribute4(Attribute4), Attribute5(Attribute5), CustomRoles(CustomRoles), GuildMemberDefaultRole(GuildMemberDefaultRole)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FCreateGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->CreateGuild(
                    MakeShared<Gs2::Guild::Request::FCreateGuildRequest>()
                        ->WithGuildModelName(GuildModelName)
                        ->WithDisplayName(DisplayName)
                        ->WithAttribute1(Attribute1)
                        ->WithAttribute2(Attribute2)
                        ->WithAttribute3(Attribute3)
                        ->WithAttribute4(Attribute4)
                        ->WithAttribute5(Attribute5)
                        ->WithJoinPolicy(JoinPolicy)
                        ->WithCustomRoles([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Guild::Model::FRoleModel>>>();
                            if (!CustomRoles.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *CustomRoles) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithGuildMemberDefaultRole(GuildMemberDefaultRole)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Guild::Domain::Model::FEzGuildDomain>(
                    Task->GetTask().Result(),
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FCreateGuildTask>> FEzUserGameSessionDomain::CreateGuild(
        FString GuildModelName,
        FString DisplayName,
        FString JoinPolicy,
        TOptional<int32> Attribute1,
        TOptional<int32> Attribute2,
        TOptional<int32> Attribute3,
        TOptional<int32> Attribute4,
        TOptional<int32> Attribute5,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles,
        TOptional<FString> GuildMemberDefaultRole
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGuildTask>>(
            this->AsShared(),
            GuildModelName,
            DisplayName,
            JoinPolicy,
            Attribute1,
            Attribute2,
            Attribute3,
            Attribute4,
            Attribute5,
            CustomRoles,
            GuildMemberDefaultRole
        );
    }

    FEzUserGameSessionDomain::FCancelRequestTask::FCancelRequestTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString GuildModelName,
        FString TargetGuildName
    ): Self(Self), GuildModelName(GuildModelName), TargetGuildName(TargetGuildName)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FCancelRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzSendMemberRequestGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Guild::Request::FDeleteRequestRequest>()
                        ->WithGuildModelName(GuildModelName)
                        ->WithTargetGuildName(TargetGuildName)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Guild::Domain::Model::FEzSendMemberRequestGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FCancelRequestTask>> FEzUserGameSessionDomain::CancelRequest(
        FString GuildModelName,
        FString TargetGuildName
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCancelRequestTask>>(
            this->AsShared(),
            GuildModelName,
            TargetGuildName
        );
    }

    Gs2::UE5::Guild::Domain::Iterator::FEzDescribeSendRequestsIteratorPtr FEzUserGameSessionDomain::SendRequests(
          const FString GuildModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Iterator::FEzDescribeSendRequestsIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            GuildModelName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeSendRequests(
        const FString GuildModelName,
        TFunction<void()> Callback
    )
    {
        return Domain->SubscribeSendRequests(
            GuildModelName,
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeSendRequests(
        const FString GuildModelName,
        Gs2::Core::Domain::CallbackID CallbackId
    )
    {
        Domain->UnsubscribeSendRequests(
            GuildModelName,
            CallbackId
        );
    }

    Gs2::UE5::Guild::Domain::Model::FEzSendMemberRequestGameSessionDomainPtr FEzUserGameSessionDomain::SendMemberRequest(
        const FString GuildModelName,
        const FString GuildName
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Model::FEzSendMemberRequestGameSessionDomain>(
            Domain->SendMemberRequest(
                GuildModelName,
                GuildName
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Guild::Domain::Iterator::FEzDescribeJoinedGuildsIteratorPtr FEzUserGameSessionDomain::JoinedGuilds(
          const TOptional<FString> GuildModelName
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Iterator::FEzDescribeJoinedGuildsIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            GuildModelName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeJoinedGuilds(TFunction<void()> Callback)
    {
        return Domain->SubscribeJoinedGuilds(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeJoinedGuilds(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeJoinedGuilds(
            CallbackId
        );
    }

    Gs2::UE5::Guild::Domain::Model::FEzJoinedGuildGameSessionDomainPtr FEzUserGameSessionDomain::JoinedGuild(
        const FString GuildModelName,
        const FString GuildName
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Model::FEzJoinedGuildGameSessionDomain>(
            Domain->JoinedGuild(
                GuildModelName,
                GuildName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
