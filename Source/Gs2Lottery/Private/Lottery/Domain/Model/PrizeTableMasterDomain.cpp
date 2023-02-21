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

#include "Lottery/Domain/Model/PrizeTableMaster.h"
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

    FPrizeTableMasterDomain::FPrizeTableMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> PrizeTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Lottery::FGs2LotteryRestClient>(Session)),
        NamespaceName(NamespaceName),
        PrizeTableName(PrizeTableName),
        ParentKey(Gs2::Lottery::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "PrizeTableMaster"
        ))
    {
    }

    FPrizeTableMasterDomain::FPrizeTableMasterDomain(
        const FPrizeTableMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FPrizeTableMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FPrizeTableMasterDomain> Self,
        const Request::FGetPrizeTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeTableMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTableMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName);
        const auto Future = Self->Client->GetPrizeTableMaster(
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
                    "PrizeTableMaster"
                );
                const auto Key = Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Lottery::Model::FPrizeTableMaster>(
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

    TSharedPtr<FAsyncTask<FPrizeTableMasterDomain::FGetTask>> FPrizeTableMasterDomain::Get(
        Request::FGetPrizeTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPrizeTableMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FPrizeTableMasterDomain> Self,
        const Request::FUpdatePrizeTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeTableMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName);
        const auto Future = Self->Client->UpdatePrizeTableMaster(
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
                    "PrizeTableMaster"
                );
                const auto Key = Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Lottery::Model::FPrizeTableMaster>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeTableMasterDomain::FUpdateTask>> FPrizeTableMasterDomain::Update(
        Request::FUpdatePrizeTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FPrizeTableMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPrizeTableMasterDomain> Self,
        const Request::FDeletePrizeTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPrizeTableMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithPrizeTableName(Self->PrizeTableName);
        const auto Future = Self->Client->DeletePrizeTableMaster(
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
                    "PrizeTableMaster"
                );
                const auto Key = Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete<Gs2::Lottery::Model::FPrizeTableMaster>(ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeTableMasterDomain::FDeleteTask>> FPrizeTableMasterDomain::Delete(
        Request::FDeletePrizeTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPrizeTableMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> PrizeTableName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null") + ":" +
            ChildType;
    }

    FString FPrizeTableMasterDomain::CreateCacheKey(
        TOptional<FString> PrizeTableName
    )
    {
        return FString() +
            (PrizeTableName.IsSet() ? *PrizeTableName : "null");
    }

    FPrizeTableMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FPrizeTableMasterDomain> Self
    ): Self(Self)
    {

    }

    FPrizeTableMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPrizeTableMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Lottery::Model::FPrizeTableMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Lottery::Model::FPrizeTableMaster>(
            Self->ParentKey,
            Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain::CreateCacheKey(
                Self->PrizeTableName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Lottery::Request::FGetPrizeTableMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "prizeTableMaster")
                    {
                        Self->Cache->Delete<Gs2::Lottery::Model::FPrizeTableMaster>(
                            Self->ParentKey,
                            Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain::CreateCacheKey(
                                Self->PrizeTableName
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
            Value = Self->Cache->Get<Gs2::Lottery::Model::FPrizeTableMaster>(
                Self->ParentKey,
                Gs2::Lottery::Domain::Model::FPrizeTableMasterDomain::CreateCacheKey(
                    Self->PrizeTableName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPrizeTableMasterDomain::FModelTask>> FPrizeTableMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPrizeTableMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

