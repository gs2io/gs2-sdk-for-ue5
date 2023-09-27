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

#include "Realtime/Domain/Model/Gs2RealtimeEzRoomDomain.h"

namespace Gs2::UE5::Realtime::Domain::Model
{

    TOptional<FString> FEzRoomDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRoomDomain::RoomName() const
    {
        return Domain->RoomName;
    }

    FEzRoomDomain::FEzRoomDomain(
        Gs2::Realtime::Domain::Model::FRoomDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzRoomDomain::FGetRoomTask::FGetRoomTask(
        TSharedPtr<FEzRoomDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRoomDomain::FGetRoomTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Realtime::Model::FEzRoom>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetRoomTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Realtime::Request::FGetRoomRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Realtime::Model::FEzRoom::FromModel(
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

    FEzRoomDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRoomDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRoomDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Realtime::Model::FEzRoomPtr> Result
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
                *Result = Gs2::UE5::Realtime::Model::FEzRoom::FromModel(Task->GetTask().Result());
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

    Gs2::Core::Domain::CallbackID FEzRoomDomain::Subscribe(TFunction<void(Gs2::UE5::Realtime::Model::FEzRoomPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Realtime::Model::FRoomPtr Item)
            {
                Callback(Gs2::UE5::Realtime::Model::FEzRoom::FromModel(Item));
            }
        );
    }

    void FEzRoomDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
