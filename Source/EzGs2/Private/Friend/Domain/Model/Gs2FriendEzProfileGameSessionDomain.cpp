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

#include "Friend/Domain/Model/Gs2FriendEzProfileGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzProfileGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzProfileGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzProfileGameSessionDomain::FEzProfileGameSessionDomain(
        Gs2::Friend::Domain::Model::FProfileAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzProfileGameSessionDomain::FUpdateProfileTask::FUpdateProfileTask(
        TSharedPtr<FEzProfileGameSessionDomain> Self,
        TOptional<FString> PublicProfile,
        TOptional<FString> FollowerProfile,
        TOptional<FString> FriendProfile
    ): Self(Self), PublicProfile(PublicProfile), FollowerProfile(FollowerProfile), FriendProfile(FriendProfile)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProfileGameSessionDomain::FUpdateProfileTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzProfileGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FUpdateProfileTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Update(
                    MakeShared<Gs2::Friend::Request::FUpdateProfileRequest>()
                        ->WithPublicProfile(PublicProfile)
                        ->WithFollowerProfile(FollowerProfile)
                        ->WithFriendProfile(FriendProfile)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzProfileGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzProfileGameSessionDomain::FUpdateProfileTask>> FEzProfileGameSessionDomain::UpdateProfile(
        TOptional<FString> PublicProfile,
        TOptional<FString> FollowerProfile,
        TOptional<FString> FriendProfile
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateProfileTask>>(
            this->AsShared(),
            PublicProfile,
            FollowerProfile,
            FriendProfile
        );
    }

    FEzProfileGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzProfileGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProfileGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Friend::Model::FEzProfilePtr> Result
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
                *Result = Gs2::UE5::Friend::Model::FEzProfile::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzProfileGameSessionDomain::FModelTask>> FEzProfileGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzProfileGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzProfilePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Friend::Model::FProfilePtr Item)
            {
                Callback(Gs2::UE5::Friend::Model::FEzProfile::FromModel(Item));
            }
        );
    }

    void FEzProfileGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
