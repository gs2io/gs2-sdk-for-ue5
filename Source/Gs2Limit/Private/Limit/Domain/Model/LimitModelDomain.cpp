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

#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FLimitModelDomain::FLimitModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> LimitName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Session)),
        NamespaceName(NamespaceName),
        LimitName(LimitName),
        ParentKey(Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "LimitModel"
        ))
    {
    }

    FLimitModelDomain::FLimitModelDomain(
        const FLimitModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        LimitName(From.LimitName),
        ParentKey(From.ParentKey)
    {

    }

    FLimitModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FLimitModelDomain> Self,
        const Request::FGetLimitModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FLimitModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FLimitModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLimitName(Self->LimitName);
        const auto Future = Self->Client->GetLimitModel(
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
                const auto ParentKey = Gs2::Limit::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "LimitModel"
                );
                const auto Key = Gs2::Limit::Domain::Model::FLimitModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Limit::Model::FLimitModel::TypeName,
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

    TSharedPtr<FAsyncTask<FLimitModelDomain::FGetTask>> FLimitModelDomain::Get(
        Request::FGetLimitModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FLimitModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> LimitName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (LimitName.IsSet() ? *LimitName : "null") + ":" +
            ChildType;
    }

    FString FLimitModelDomain::CreateCacheKey(
        TOptional<FString> LimitName
    )
    {
        return FString("") +
            (LimitName.IsSet() ? *LimitName : "null");
    }

    FLimitModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FLimitModelDomain> Self
    ): Self(Self)
    {

    }

    FLimitModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FLimitModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FLimitModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Limit::Model::FLimitModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Limit::Model::FLimitModel>(
            Self->ParentKey,
            Gs2::Limit::Domain::Model::FLimitModelDomain::CreateCacheKey(
                Self->LimitName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Limit::Request::FGetLimitModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Limit::Domain::Model::FLimitModelDomain::CreateCacheKey(
                    Self->LimitName
                );
                Self->Cache->Put(
                    Gs2::Limit::Model::FLimitModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "limitModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Limit::Model::FLimitModel>(
                Self->ParentKey,
                Gs2::Limit::Domain::Model::FLimitModelDomain::CreateCacheKey(
                    Self->LimitName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FLimitModelDomain::FModelTask>> FLimitModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FLimitModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

