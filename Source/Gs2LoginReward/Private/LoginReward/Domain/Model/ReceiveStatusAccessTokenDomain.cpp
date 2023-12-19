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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "LoginReward/Domain/Model/ReceiveStatusAccessToken.h"
#include "LoginReward/Domain/Model/ReceiveStatus.h"
#include "LoginReward/Domain/Model/Namespace.h"
#include "LoginReward/Domain/Model/BonusModelMaster.h"
#include "LoginReward/Domain/Model/CurrentBonusMaster.h"
#include "LoginReward/Domain/Model/BonusModel.h"
#include "LoginReward/Domain/Model/User.h"
#include "LoginReward/Domain/Model/UserAccessToken.h"
#include "LoginReward/Domain/Model/Bonus.h"
#include "LoginReward/Domain/Model/BonusAccessToken.h"
#include "LoginReward/Domain/Model/ReceiveStatus.h"
#include "LoginReward/Domain/Model/ReceiveStatusAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::LoginReward::Domain::Model
{

    FReceiveStatusAccessTokenDomain::FReceiveStatusAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> BonusModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::LoginReward::FGs2LoginRewardRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        BonusModelName(BonusModelName),
        ParentKey(Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "ReceiveStatus"
        ))
    {
    }

    FReceiveStatusAccessTokenDomain::FReceiveStatusAccessTokenDomain(
        const FReceiveStatusAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        BonusModelName(From.BonusModelName),
        ParentKey(From.ParentKey)
    {

    }

    FReceiveStatusAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FReceiveStatusAccessTokenDomain>& Self,
        const Request::FGetReceiveStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveStatusAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveStatusAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FReceiveStatus>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithBonusModelName(Self->BonusModelName);
        const auto Future = Self->Client->GetReceiveStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "ReceiveStatus"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetBonusModelName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::LoginReward::Model::FReceiveStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetBonusModel() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "BonusModel"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FBonusModelDomain::CreateCacheKey(
                    ResultModel->GetBonusModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::LoginReward::Model::FBonusModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetBonusModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveStatusAccessTokenDomain::FGetTask>> FReceiveStatusAccessTokenDomain::Get(
        Request::FGetReceiveStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FReceiveStatusAccessTokenDomain::FMarkReceivedTask::FMarkReceivedTask(
        const TSharedPtr<FReceiveStatusAccessTokenDomain>& Self,
        const Request::FMarkReceivedRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FReceiveStatusAccessTokenDomain::FMarkReceivedTask::FMarkReceivedTask(
        const FMarkReceivedTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveStatusAccessTokenDomain::FMarkReceivedTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FReceiveStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithBonusModelName(Self->BonusModelName);
        const auto Future = Self->Client->MarkReceived(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "ReceiveStatus"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetBonusModelName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::LoginReward::Model::FReceiveStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetBonusModel() != nullptr)
            {
                const auto ParentKey = Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "BonusModel"
                );
                const auto Key = Gs2::LoginReward::Domain::Model::FBonusModelDomain::CreateCacheKey(
                    ResultModel->GetBonusModel()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::LoginReward::Model::FBonusModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetBonusModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveStatusAccessTokenDomain::FMarkReceivedTask>> FReceiveStatusAccessTokenDomain::MarkReceived(
        Request::FMarkReceivedRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FMarkReceivedTask>>(this->AsShared(), Request);
    }

    FString FReceiveStatusAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> BonusModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (BonusModelName.IsSet() ? *BonusModelName : "null") + ":" +
            ChildType;
    }

    FString FReceiveStatusAccessTokenDomain::CreateCacheKey(
        TOptional<FString> BonusModelName
    )
    {
        return FString("") +
            (BonusModelName.IsSet() ? *BonusModelName : "null");
    }

    FReceiveStatusAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FReceiveStatusAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FReceiveStatusAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FReceiveStatusAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FReceiveStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::LoginReward::Model::FReceiveStatus> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::LoginReward::Model::FReceiveStatus>(
            Self->ParentKey,
            Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                Self->BonusModelName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::LoginReward::Request::FGetReceiveStatusRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    Self->BonusModelName
                );
                Self->Gs2->Cache->Put(
                    Gs2::LoginReward::Model::FReceiveStatus::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "receiveStatus")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::LoginReward::Model::FReceiveStatus>(
                Self->ParentKey,
                Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                    Self->BonusModelName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReceiveStatusAccessTokenDomain::FModelTask>> FReceiveStatusAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveStatusAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FReceiveStatusAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::LoginReward::Model::FReceiveStatusPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::LoginReward::Model::FReceiveStatus::TypeName,
            ParentKey,
            Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                BonusModelName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::LoginReward::Model::FReceiveStatus>(obj));
            }
        );
    }

    void FReceiveStatusAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::LoginReward::Model::FReceiveStatus::TypeName,
            ParentKey,
            Gs2::LoginReward::Domain::Model::FReceiveStatusDomain::CreateCacheKey(
                BonusModelName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

