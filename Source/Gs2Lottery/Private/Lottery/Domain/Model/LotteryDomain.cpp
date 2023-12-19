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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/Namespace.h"
#include "Lottery/Domain/Model/LotteryModelMaster.h"
#include "Lottery/Domain/Model/PrizeTableMaster.h"
#include "Lottery/Domain/Model/LotteryModel.h"
#include "Lottery/Domain/Model/PrizeTable.h"
#include "Lottery/Domain/Model/Lottery.h"
#include "Lottery/Domain/Model/LotteryAccessToken.h"
#include "Lottery/Domain/Model/Probability.h"
#include "Lottery/Domain/Model/ProbabilityAccessToken.h"
#include "Lottery/Domain/Model/CurrentLotteryMaster.h"
#include "Lottery/Domain/Model/PrizeLimit.h"
#include "Lottery/Domain/Model/BoxItems.h"
#include "Lottery/Domain/Model/BoxItemsAccessToken.h"
#include "Lottery/Domain/Model/User.h"
#include "Lottery/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FLotteryDomain::FLotteryDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Lottery::Domain::FGs2LotteryDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Lottery::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Lottery"
        ))
    {
    }

    FLotteryDomain::FLotteryDomain(
        const FLotteryDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FLotteryDomain::FDrawTask::FDrawTask(
        const TSharedPtr<FLotteryDomain>& Self,
        const Request::FDrawByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryDomain::FDrawTask::FDrawTask(
        const FDrawTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryDomain::FDrawTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FLotteryDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DrawByUserId(
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
            
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                *Self->UserId,
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

    TSharedPtr<FAsyncTask<FLotteryDomain::FDrawTask>> FLotteryDomain::Draw(
        Request::FDrawByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDrawTask>>(this->AsShared(), Request);
    }

    FLotteryDomain::FPredictionTask::FPredictionTask(
        const TSharedPtr<FLotteryDomain>& Self,
        const Request::FPredictionByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryDomain::FPredictionTask::FPredictionTask(
        const FPredictionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryDomain::FPredictionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Lottery::Model::FDrawnPrize>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PredictionByUserId(
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
            
        }
        *Result = ResultModel->GetItems();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryDomain::FPredictionTask>> FLotteryDomain::Prediction(
        Request::FPredictionByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPredictionTask>>(this->AsShared(), Request);
    }

    FLotteryDomain::FDrawWithRandomSeedTask::FDrawWithRandomSeedTask(
        const TSharedPtr<FLotteryDomain>& Self,
        const Request::FDrawWithRandomSeedByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryDomain::FDrawWithRandomSeedTask::FDrawWithRandomSeedTask(
        const FDrawWithRandomSeedTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryDomain::FDrawWithRandomSeedTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FLotteryDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DrawWithRandomSeedByUserId(
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
            
        }
        if (ResultModel && ResultModel->GetStampSheet())
        {
            const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
                Self->Gs2,
                *Self->UserId,
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

    TSharedPtr<FAsyncTask<FLotteryDomain::FDrawWithRandomSeedTask>> FLotteryDomain::DrawWithRandomSeed(
        Request::FDrawWithRandomSeedByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDrawWithRandomSeedTask>>(this->AsShared(), Request);
    }

    FString FLotteryDomain::CreateCacheParentKey(
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

    FString FLotteryDomain::CreateCacheKey(
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

