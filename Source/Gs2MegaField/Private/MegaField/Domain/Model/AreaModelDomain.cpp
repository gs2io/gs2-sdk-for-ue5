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

#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/Namespace.h"
#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/AreaModelMaster.h"
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Domain/Model/LayerModelMaster.h"
#include "MegaField/Domain/Model/CurrentFieldMaster.h"
#include "MegaField/Domain/Model/User.h"
#include "MegaField/Domain/Model/UserAccessToken.h"
#include "MegaField/Domain/Model/Spatial.h"
#include "MegaField/Domain/Model/SpatialAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::MegaField::Domain::Model
{

    FAreaModelDomain::FAreaModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> AreaModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Session)),
        NamespaceName(NamespaceName),
        AreaModelName(AreaModelName),
        ParentKey(Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "AreaModel"
        ))
    {
    }

    FAreaModelDomain::FAreaModelDomain(
        const FAreaModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FAreaModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FAreaModelDomain> Self,
        const Request::FGetAreaModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->GetAreaModel(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "AreaModel"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::MegaField::Model::FAreaModel>(
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

    TSharedPtr<FAsyncTask<FAreaModelDomain::FGetTask>> FAreaModelDomain::Get(
        Request::FGetAreaModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIteratorPtr FAreaModelDomain::LayerModels(
    ) const
    {
        return MakeShared<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator>(
            Cache,
            Client,
            NamespaceName,
            AreaModelName
        );
    }

    TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelDomain> FAreaModelDomain::LayerModel(
        const FString LayerModelName
    ) const
    {
        return MakeShared<Gs2::MegaField::Domain::Model::FLayerModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AreaModelName,
            LayerModelName
        );
    }

    FString FAreaModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> AreaModelName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" +
            ChildType;
    }

    FString FAreaModelDomain::CreateCacheKey(
        TOptional<FString> AreaModelName
    )
    {
        return FString() +
            (AreaModelName.IsSet() ? *AreaModelName : "null");
    }

    FAreaModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FAreaModelDomain> Self
    ): Self(Self)
    {

    }

    FAreaModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::MegaField::Model::FAreaModel>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                Self->AreaModelName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::MegaField::Request::FGetAreaModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "areaModel")
                    {
                        Self->Cache->Delete<Gs2::MegaField::Model::FAreaModel>(
                            Self->ParentKey,
                            Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                                Self->AreaModelName
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
            Value = Self->Cache->Get<Gs2::MegaField::Model::FAreaModel>(
                Self->ParentKey,
                Gs2::MegaField::Domain::Model::FAreaModelDomain::CreateCacheKey(
                    Self->AreaModelName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelDomain::FModelTask>> FAreaModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAreaModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

