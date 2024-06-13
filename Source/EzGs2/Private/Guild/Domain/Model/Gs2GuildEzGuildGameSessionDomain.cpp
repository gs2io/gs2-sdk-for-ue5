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
        Gs2::UE5::Util::FGuildGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

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

    Gs2::UE5::Guild::Domain::Iterator::FEzDescribeReceiveMemberRequestsIteratorPtr FEzGuildGameSessionDomain::ReceiveMemberRequests(
    ) const
    {
        return MakeShared<Gs2::UE5::Guild::Domain::Iterator::FEzDescribeReceiveMemberRequestsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    FEzGuildGameSessionDomain::FUpdateTask::FUpdateTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self,
        FString DisplayName,
        FString JoinPolicy,
        TOptional<int32> Attribute1,
        TOptional<int32> Attribute2,
        TOptional<int32> Attribute3,
        TOptional<int32> Attribute4,
        TOptional<int32> Attribute5,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> CustomRoles,
        TOptional<FString> GuildMemberDefaultRole
    ): Self(Self), DisplayName(DisplayName), JoinPolicy(JoinPolicy), Attribute1(Attribute1), Attribute2(Attribute2), Attribute3(Attribute3), Attribute4(Attribute4), Attribute5(Attribute5), CustomRoles(CustomRoles), GuildMemberDefaultRole(GuildMemberDefaultRole)
    {

    }
    
    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FUpdateTask::Action(
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
    
    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FUpdateTask>> FEzGuildGameSessionDomain::Update(
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
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(
            this->AsShared(),
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

    FEzGuildGameSessionDomain::FDeleteMemberTask::FDeleteMemberTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self,
        FString TargetUserId
    ): Self(Self), TargetUserId(TargetUserId)
    {

    }
    
    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FDeleteMemberTask::Action(
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
    
    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FDeleteMemberTask>> FEzGuildGameSessionDomain::DeleteMember(
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteMemberTask>>(
            this->AsShared(),
            TargetUserId
        );
    }

    FEzGuildGameSessionDomain::FUpdateMemberRoleTask::FUpdateMemberRoleTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self,
        FString TargetUserId,
        FString RoleName
    ): Self(Self), TargetUserId(TargetUserId), RoleName(RoleName)
    {

    }
    
    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FUpdateMemberRoleTask::Action(
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
    
    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FUpdateMemberRoleTask>> FEzGuildGameSessionDomain::UpdateMemberRole(
        FString TargetUserId,
        FString RoleName
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateMemberRoleTask>>(
            this->AsShared(),
            TargetUserId,
            RoleName
        );
    }

    FEzGuildGameSessionDomain::FDeleteTask::FDeleteTask(
        TSharedPtr<FEzGuildGameSessionDomain> Self
    ): Self(Self)
    {

    }
    
    Gs2::Core::Model::FGs2ErrorPtr FEzGuildGameSessionDomain::FDeleteTask::Action(
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
    
    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FDeleteTask>> FEzGuildGameSessionDomain::Delete()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared());
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

    TSharedPtr<FAsyncTask<FEzGuildGameSessionDomain::FModelTask>> FEzGuildGameSessionDomain::Model()
    {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(
            this->AsShared()
        );
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
