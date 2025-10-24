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

#include "Guild/Domain/Model/Gs2GuildEzGuildGameSessionDomain.h"

namespace Gs2::UE5::Guild::Domain::Model
{

    TOptional<FString> FEzGuildGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGuildGameSessionDomain::GuildModelName() const
    {
        return Domain->GuildModelName;
    }

    TOptional<FString> FEzGuildGameSessionDomain::GuildName() const
    {
        return Domain->GuildName();
    }

    FEzGuildGameSessionDomain::FEzGuildGameSessionDomain(
        Gs2::Guild::Domain::Model::FGuildAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzGuildGameSessionDomain::FUpdateGuildTask::FUpdateGuildTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self,
        FString DisplayName,
        FString JoinPolicy,
        TOptional<int32> Attribute1,
        TOptional<int32> Attribute2,
        TOptional<int32> Attribute3,
        TOptional<int32> Attribute4,
        TOptional<int32> Attribute5,
        TOptional<FString> Metadata,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles,
        TOptional<FString> GuildMemberDefaultRole
    ): Self(Self), DisplayName(DisplayName), JoinPolicy(JoinPolicy), Attribute1(Attribute1), Attribute2(Attribute2), Attribute3(Attribute3), Attribute4(Attribute4), Attribute5(Attribute5), Metadata(Metadata), CustomRoles(CustomRoles), GuildMemberDefaultRole(GuildMemberDefaultRole)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FUpdateGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Update(
                    MakeShared<Gs2::Guild::Request::FUpdateGuildRequest>()
                        ->WithDisplayName(DisplayName)
                        ->WithAttribute1(Attribute1)
                        ->WithAttribute2(Attribute2)
                        ->WithAttribute3(Attribute3)
                        ->WithAttribute4(Attribute4)
                        ->WithAttribute5(Attribute5)
                        ->WithMetadata(Metadata)
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

    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FUpdateGuildTask>> FEzGuildGameSessionDomain::UpdateGuild(
        FString DisplayName,
        FString JoinPolicy,
        TOptional<int32> Attribute1,
        TOptional<int32> Attribute2,
        TOptional<int32> Attribute3,
        TOptional<int32> Attribute4,
        TOptional<int32> Attribute5,
        TOptional<FString> Metadata,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles,
        TOptional<FString> GuildMemberDefaultRole
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateGuildTask>>(
            this->AsShared(),
            DisplayName,
            JoinPolicy,
            Attribute1,
            Attribute2,
            Attribute3,
            Attribute4,
            Attribute5,
            Metadata,
            CustomRoles,
            GuildMemberDefaultRole
        );
    }

    FEzGuildGameSessionDomain::FDeleteMemberFromGuildTask::FDeleteMemberFromGuildTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self,
        FString TargetUserId
    ): Self(Self), TargetUserId(TargetUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FDeleteMemberFromGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->DeleteMember(
                    MakeShared<Gs2::Guild::Request::FDeleteMemberRequest>()
                        ->WithTargetUserId(TargetUserId)
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

    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FDeleteMemberFromGuildTask>> FEzGuildGameSessionDomain::DeleteMemberFromGuild(
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteMemberFromGuildTask>>(
            this->AsShared(),
            TargetUserId
        );
    }

    FEzGuildGameSessionDomain::FUpdateGuildMemberRoleTask::FUpdateGuildMemberRoleTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self,
        FString TargetUserId,
        FString RoleName
    ): Self(Self), TargetUserId(TargetUserId), RoleName(RoleName)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FUpdateGuildMemberRoleTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->UpdateMemberRole(
                    MakeShared<Gs2::Guild::Request::FUpdateMemberRoleRequest>()
                        ->WithTargetUserId(TargetUserId)
                        ->WithRoleName(RoleName)
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

    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FUpdateGuildMemberRoleTask>> FEzGuildGameSessionDomain::UpdateGuildMemberRole(
        FString TargetUserId,
        FString RoleName
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateGuildMemberRoleTask>>(
            this->AsShared(),
            TargetUserId,
            RoleName
        );
    }

    FEzGuildGameSessionDomain::FDeleteGuildTask::FDeleteGuildTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FDeleteGuildTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzGuildGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Guild::Request::FDeleteGuildRequest>()
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

    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FDeleteGuildTask>> FEzGuildGameSessionDomain::DeleteGuild(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteGuildTask>>(
            this->AsShared()
        );
    }

    FEzGuildGameSessionDomain::FAddIgnoreUserTask::FAddIgnoreUserTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self,
        FString UserId
    ): Self(Self), UserId(UserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FAddIgnoreUserTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->AddIgnoreUser(
                    MakeShared<Gs2::Guild::Request::FAddIgnoreUserRequest>()
                        ->WithUserId(UserId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FAddIgnoreUserTask>> FEzGuildGameSessionDomain::AddIgnoreUser(
        FString UserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FAddIgnoreUserTask>>(
            this->AsShared(),
            UserId
        );
    }

    FEzGuildGameSessionDomain::FPromoteSeniorMemberTask::FPromoteSeniorMemberTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FPromoteSeniorMemberTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Guild::Domain::Model::FEzLastGuildMasterActivityGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PromoteSeniorMember(
                    MakeShared<Gs2::Guild::Request::FPromoteSeniorMemberRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Guild::Domain::Model::FEzLastGuildMasterActivityGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FPromoteSeniorMemberTask>> FEzGuildGameSessionDomain::PromoteSeniorMember(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPromoteSeniorMemberTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Guild::Domain::Iterator::FEzDescribeReceiveRequestsIteratorPtr FEzGuildGameSessionDomain::ReceiveRequests(
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Iterator::FEzDescribeReceiveRequestsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzGuildGameSessionDomain::SubscribeReceiveRequests(TFunction<void()> Callback)
    {
        return Domain->SubscribeReceiveRequests(
            Callback
        );
    }

    void FEzGuildGameSessionDomain::UnsubscribeReceiveRequests(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeReceiveRequests(
            CallbackId
        );
    }

    Gs2::UE5::Guild::Domain::Iterator::FEzDescribeIgnoreUsersIteratorPtr FEzGuildGameSessionDomain::IgnoreUsers(
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Iterator::FEzDescribeIgnoreUsersIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzGuildGameSessionDomain::SubscribeIgnoreUsers(TFunction<void()> Callback)
    {
        return Domain->SubscribeIgnoreUsers(
            Callback
        );
    }

    void FEzGuildGameSessionDomain::UnsubscribeIgnoreUsers(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeIgnoreUsers(
            CallbackId
        );
    }

    Gs2::UE5::Guild::Domain::Model::FEzReceiveMemberRequestGameSessionDomainPtr FEzGuildGameSessionDomain::ReceiveMemberRequest(
        const FString FromUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Model::FEzReceiveMemberRequestGameSessionDomain>(
            Domain->ReceiveMemberRequest(
                FromUserId
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomainPtr FEzGuildGameSessionDomain::IgnoreUser(
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Model::FEzIgnoreUserGameSessionDomain>(
            Domain->IgnoreUser(
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Guild::Domain::Model::FEzLastGuildMasterActivityGameSessionDomainPtr FEzGuildGameSessionDomain::LastGuildMasterActivity(
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Model::FEzLastGuildMasterActivityGameSessionDomain>(
            Domain->LastGuildMasterActivity(
            ),
            GameSession,
            ConnectionValue
        );
    }

    FEzGuildGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Guild::Model::FEzGuildPtr> Result
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
                *Result = Gs2::UE5::Guild::Model::FEzGuild::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FModelTask>> FEzGuildGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzGuildGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Guild::Model::FEzGuildPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Guild::Model::FGuildPtr Item)
            {
                Callback(Gs2::UE5::Guild::Model::FEzGuild::FromModel(Item));
            }
        );
    }

    void FEzGuildGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
