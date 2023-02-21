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

#include "Chat/Domain/Model/Gs2ChatEzRoomDomain.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    TOptional<FString> FEzRoomDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRoomDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzRoomDomain::RoomName() const
    {
        return Domain->RoomName;
    }

    TOptional<FString> FEzRoomDomain::Password() const
    {
        return Domain->Password;
    }

    FEzRoomDomain::FEzRoomDomain(
        Gs2::Chat::Domain::Model::FRoomDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRoomDomain::FGetRoomTask::FGetRoomTask(
        TSharedPtr<FEzRoomDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRoomDomain::FGetRoomTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Model::FEzRoom>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetRoomTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Chat::Request::FGetRoomRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Chat::Model::FEzRoom::FromModel(
                    Task->GetTask().Result()
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

    TSharedPtr<FAsyncTask<FEzRoomDomain::FGetRoomTask>> FEzRoomDomain::GetRoom(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetRoomTask>>(
            this->AsShared()
        );
    }

    Gs2::UE5::Chat::Domain::Model::FEzMessageDomainPtr FEzRoomDomain::Message(
        const FString MessageName
    ) const
    {
        return MakeShared<Gs2::UE5::Chat::Domain::Model::FEzMessageDomain>(
            Domain->Message(
                MessageName
            ),
            ProfileValue
        );
    }

    FEzRoomDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRoomDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRoomDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Chat::Model::FEzRoomPtr> Result
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
                *Result = Gs2::UE5::Chat::Model::FEzRoom::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRoomDomain::FModelTask>> FEzRoomDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
