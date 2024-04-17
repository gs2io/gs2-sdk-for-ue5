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

#include "LoginReward/Domain/Model/BonusAccessToken.h"
#include "LoginReward/Domain/Model/Bonus.h"
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
#include "LoginReward/Domain/SpeculativeExecutor/Transaction/ReceiveByUserIdSpeculativeExecutor.h"
#include "LoginReward/Domain/SpeculativeExecutor/Transaction/MissedReceiveByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::LoginReward::Domain::Model
{

    FBonusAccessTokenDomain::FBonusAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::LoginReward::FGs2LoginRewardRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::LoginReward::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Bonus"
        ))
    {
    }

    FBonusAccessTokenDomain::FBonusAccessTokenDomain(
        const FBonusAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FBonusAccessTokenDomain::FReceiveTask::FReceiveTask(
        const TSharedPtr<FBonusAccessTokenDomain>& Self,
        const Request::FReceiveRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FBonusAccessTokenDomain::FReceiveTask::FReceiveTask(
        const FReceiveTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBonusAccessTokenDomain::FReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FReceiveByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FReceiveByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->Receive(
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
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBonusAccessTokenDomain::FReceiveTask>> FBonusAccessTokenDomain::Receive(
        Request::FReceiveRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FBonusAccessTokenDomain::FMissedReceiveTask::FMissedReceiveTask(
        const TSharedPtr<FBonusAccessTokenDomain>& Self,
        const Request::FMissedReceiveRequestPtr Request,
        bool SpeculativeExecute
    ): Self(Self), Request(Request), SpeculativeExecute(SpeculativeExecute)
    {

    }

    FBonusAccessTokenDomain::FMissedReceiveTask::FMissedReceiveTask(
        const FMissedReceiveTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request), SpeculativeExecute(From.SpeculativeExecute)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBonusAccessTokenDomain::FMissedReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());

        if (SpeculativeExecute) {
            const auto SpeculativeExecuteFuture = Transaction::SpeculativeExecutor::FMissedReceiveByUserIdSpeculativeExecutor::Execute(
                Self->Gs2,
                Self->Service,
                Self->AccessToken,
                Request::FMissedReceiveByUserIdRequest::FromJson(Request->ToJson())
            );
            SpeculativeExecuteFuture->StartSynchronousTask();
            if (SpeculativeExecuteFuture->GetTask().IsError())
            {
                return SpeculativeExecuteFuture->GetTask().Error();
            }
            const auto Commit = SpeculativeExecuteFuture->GetTask().Result();
            SpeculativeExecuteFuture->EnsureCompletion();

            if (Commit.IsValid()) {
                (*Commit)();
            }
        }
        const auto Future = Self->Client->MissedReceive(
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
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                Self->AccessToken,
                false,
                *ResultModel->GetTransactionId(),
                *ResultModel->GetStampSheet(),
                *ResultModel->GetStampSheetEncryptionKeyId()
            );
            const auto Future3 = Transaction->Wait(true);
            Future3->StartSynchronousTask();
            if (Future3->GetTask().IsError())
            {
                return Future3->GetTask().Error();
            }
        }
        if (ResultModel != nullptr)
        {
            Self->AutoRunStampSheet = ResultModel->GetAutoRunStampSheet();
            Self->TransactionId = ResultModel->GetTransactionId();
        }
        *Result = Self;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBonusAccessTokenDomain::FMissedReceiveTask>> FBonusAccessTokenDomain::MissedReceive(
        Request::FMissedReceiveRequestPtr Request,
        bool SpeculativeExecute
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FMissedReceiveTask>>(this->AsShared(), Request, SpeculativeExecute);
    }

    FString FBonusAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FBonusAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

