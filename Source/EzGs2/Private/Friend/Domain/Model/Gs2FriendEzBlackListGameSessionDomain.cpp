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

#include "Friend/Domain/Model/Gs2FriendEzBlackListGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzBlackListGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBlackListGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzBlackListGameSessionDomain::FEzBlackListGameSessionDomain(
        Gs2::Friend::Domain::Model::FBlackListAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzBlackListGameSessionDomain::FRegisterBlackListTask::FRegisterBlackListTask(
        TSharedPtr<FEzBlackListGameSessionDomain> Self,
        FString TargetUserId
    ): Self(Self), TargetUserId(TargetUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBlackListGameSessionDomain::FRegisterBlackListTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Register(
                    MakeShared<Gs2::Friend::Request::FRegisterBlackListRequest>()
                        ->WithTargetUserId(TargetUserId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzBlackListGameSessionDomain::FRegisterBlackListTask>> FEzBlackListGameSessionDomain::RegisterBlackList(
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRegisterBlackListTask>>(
            this->AsShared(),
            TargetUserId
        );
    }

    FEzBlackListGameSessionDomain::FUnregisterBlackListTask::FUnregisterBlackListTask(
        TSharedPtr<FEzBlackListGameSessionDomain> Self,
        FString TargetUserId
    ): Self(Self), TargetUserId(TargetUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBlackListGameSessionDomain::FUnregisterBlackListTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Unregister(
                    MakeShared<Gs2::Friend::Request::FUnregisterBlackListRequest>()
                        ->WithTargetUserId(TargetUserId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzBlackListGameSessionDomain::FUnregisterBlackListTask>> FEzBlackListGameSessionDomain::UnregisterBlackList(
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUnregisterBlackListTask>>(
            this->AsShared(),
            TargetUserId
        );
    }

    FEzBlackListGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzBlackListGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBlackListGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Friend::Model::FEzBlackListPtr> Result
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
                *Result = Gs2::UE5::Friend::Model::FEzBlackList::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzBlackListGameSessionDomain::FModelTask>> FEzBlackListGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzBlackListGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzBlackListPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Friend::Model::FBlackListPtr Item)
            {
                Callback(Gs2::UE5::Friend::Model::FEzBlackList::FromModel(Item));
            }
        );
    }

    void FEzBlackListGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
