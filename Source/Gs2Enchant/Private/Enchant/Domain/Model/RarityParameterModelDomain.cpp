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

#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Domain/Model/BalanceParameterModel.h"
#include "Enchant/Domain/Model/BalanceParameterModelMaster.h"
#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/CurrentParameterMaster.h"
#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Domain/Model/BalanceParameterStatus.h"
#include "Enchant/Domain/Model/BalanceParameterStatusAccessToken.h"
#include "Enchant/Domain/Model/RarityParameterStatus.h"
#include "Enchant/Domain/Model/RarityParameterStatusAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Enchant::Domain::Model
{

    FRarityParameterModelDomain::FRarityParameterModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ParameterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Enchant::FGs2EnchantRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParameterName(ParameterName),
        ParentKey(Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RarityParameterModel"
        ))
    {
    }

    FRarityParameterModelDomain::FRarityParameterModelDomain(
        const FRarityParameterModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParameterName(From.ParameterName),
        ParentKey(From.ParentKey)
    {

    }

    FRarityParameterModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FRarityParameterModelDomain> Self,
        const Request::FGetRarityParameterModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithParameterName(Self->ParameterName);
        const auto Future = Self->Client->GetRarityParameterModel(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RarityParameterModel"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterModel::TypeName,
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

    TSharedPtr<FAsyncTask<FRarityParameterModelDomain::FGetTask>> FRarityParameterModelDomain::Get(
        Request::FGetRarityParameterModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FRarityParameterModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ParameterName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ParameterName.IsSet() ? *ParameterName : "null") + ":" +
            ChildType;
    }

    FString FRarityParameterModelDomain::CreateCacheKey(
        TOptional<FString> ParameterName
    )
    {
        return FString("") +
            (ParameterName.IsSet() ? *ParameterName : "null");
    }

    FRarityParameterModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FRarityParameterModelDomain> Self
    ): Self(Self)
    {

    }

    FRarityParameterModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Enchant::Model::FRarityParameterModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Enchant::Model::FRarityParameterModel>(
            Self->ParentKey,
            Gs2::Enchant::Domain::Model::FRarityParameterModelDomain::CreateCacheKey(
                Self->ParameterName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Enchant::Request::FGetRarityParameterModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterModelDomain::CreateCacheKey(
                    Self->ParameterName
                );
                Self->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "rarityParameterModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Enchant::Model::FRarityParameterModel>(
                Self->ParentKey,
                Gs2::Enchant::Domain::Model::FRarityParameterModelDomain::CreateCacheKey(
                    Self->ParameterName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRarityParameterModelDomain::FModelTask>> FRarityParameterModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRarityParameterModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

