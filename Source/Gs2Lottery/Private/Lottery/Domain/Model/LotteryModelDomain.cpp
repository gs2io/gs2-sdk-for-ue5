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

#include "Lottery/Domain/Model/LotteryModel.h"
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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Lottery::Domain::Model
{

    FLotteryModelDomain::FLotteryModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LotteryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Session)),
        NamespaceName(NamespaceName),
        LotteryName(LotteryName),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "LotteryModel"
        ))
    {
    }

    FLotteryModelDomain::FLotteryModelDomain(
        const FLotteryModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FLotteryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FLotteryModelDomain> Self,
        const Request::FGetLotteryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLotteryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FLotteryModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLotteryName(Self->LotteryName);
        const auto Future = Self->Client->GetLotteryModel(
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
                const auto ParentKey = Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "LotteryModel"
                );
                const auto Key = Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Lottery::Model::FLotteryModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryModelDomain::FGetTask>> FLotteryModelDomain::Get(
        Request::FGetLotteryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FLotteryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> LotteryName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (LotteryName.IsSet() ? *LotteryName : "null") + ":" +
            ChildType;
    }

    FString FLotteryModelDomain::CreateCacheKey(
        TOptional<FString> LotteryName
    )
    {
        return FString() +
            (LotteryName.IsSet() ? *LotteryName : "null");
    }

    FLotteryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FLotteryModelDomain> Self
    ): Self(Self)
    {

    }

    FLotteryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLotteryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FLotteryModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Lottery::Model::FLotteryModel>(
            Self->ParentKey,
            Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                Self->LotteryName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Lottery::Request::FGetLotteryModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "lotteryModel")
                    {
                        Self->Cache->Delete<Gs2::Lottery::Model::FLotteryModel>(
                            Self->ParentKey,
                            Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                                Self->LotteryName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Lottery::Model::FLotteryModel>(
                Self->ParentKey,
                Gs2::Lottery::Domain::Model::FLotteryModelDomain::CreateCacheKey(
                    Self->LotteryName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLotteryModelDomain::FModelTask>> FLotteryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLotteryModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

