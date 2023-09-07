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

#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Domain/Model/IncrementalRateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Exchange::Domain::Model
{

    FIncrementalRateModelDomain::FIncrementalRateModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RateName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Session)),
        NamespaceName(NamespaceName),
        RateName(RateName),
        ParentKey(Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "IncrementalRateModel"
        ))
    {
    }

    FIncrementalRateModelDomain::FIncrementalRateModelDomain(
        const FIncrementalRateModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RateName(From.RateName),
        ParentKey(From.ParentKey)
    {

    }

    FIncrementalRateModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FIncrementalRateModelDomain> Self,
        const Request::FGetIncrementalRateModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FIncrementalRateModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementalRateModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FIncrementalRateModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRateName(Self->RateName);
        const auto Future = Self->Client->GetIncrementalRateModel(
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
                const auto ParentKey = Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "IncrementalRateModel"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FIncrementalRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Exchange::Model::FIncrementalRateModel::TypeName,
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

    TSharedPtr<FAsyncTask<FIncrementalRateModelDomain::FGetTask>> FIncrementalRateModelDomain::Get(
        Request::FGetIncrementalRateModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FIncrementalRateModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RateName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RateName.IsSet() ? *RateName : "null") + ":" +
            ChildType;
    }

    FString FIncrementalRateModelDomain::CreateCacheKey(
        TOptional<FString> RateName
    )
    {
        return FString("") +
            (RateName.IsSet() ? *RateName : "null");
    }

    FIncrementalRateModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FIncrementalRateModelDomain> Self
    ): Self(Self)
    {

    }

    FIncrementalRateModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementalRateModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Model::FIncrementalRateModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Exchange::Model::FIncrementalRateModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Exchange::Model::FIncrementalRateModel>(
            Self->ParentKey,
            Gs2::Exchange::Domain::Model::FIncrementalRateModelDomain::CreateCacheKey(
                Self->RateName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Exchange::Request::FGetIncrementalRateModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Exchange::Domain::Model::FIncrementalRateModelDomain::CreateCacheKey(
                    Self->RateName
                );
                Self->Cache->Put(
                    Gs2::Exchange::Model::FIncrementalRateModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "incrementalRateModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Exchange::Model::FIncrementalRateModel>(
                Self->ParentKey,
                Gs2::Exchange::Domain::Model::FIncrementalRateModelDomain::CreateCacheKey(
                    Self->RateName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIncrementalRateModelDomain::FModelTask>> FIncrementalRateModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FIncrementalRateModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

