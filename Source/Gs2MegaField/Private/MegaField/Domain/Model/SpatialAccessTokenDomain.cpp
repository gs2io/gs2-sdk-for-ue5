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

#include "MegaField/Domain/Model/SpatialAccessToken.h"
#include "MegaField/Domain/Model/Spatial.h"
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

    FSpatialAccessTokenDomain::FSpatialAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> AreaModelName,
        const TOptional<FString> LayerModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        AreaModelName(AreaModelName),
        LayerModelName(LayerModelName),
        ParentKey(Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Spatial"
        ))
    {
    }

    FSpatialAccessTokenDomain::FSpatialAccessTokenDomain(
        const FSpatialAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FSpatialAccessTokenDomain::FPutPositionTask::FPutPositionTask(
        const TSharedPtr<FSpatialAccessTokenDomain> Self,
        const Request::FPutPositionRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSpatialAccessTokenDomain::FPutPositionTask::FPutPositionTask(
        const FPutPositionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSpatialAccessTokenDomain::FPutPositionTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->PutPosition(
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
                const auto ParentKey = Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "Spatial"
                );
                const auto Key = Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetAreaModelName(),
                    ResultModel->GetItem()->GetLayerModelName()
                );
                Self->Cache->Put<Gs2::MegaField::Model::FSpatial>(
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

    TSharedPtr<FAsyncTask<FSpatialAccessTokenDomain::FPutPositionTask>> FSpatialAccessTokenDomain::PutPosition(
        Request::FPutPositionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPutPositionTask>>(this->AsShared(), Request);
    }

    FSpatialAccessTokenDomain::FFetchPositionTask::FFetchPositionTask(
        const TSharedPtr<FSpatialAccessTokenDomain> Self,
        const Request::FFetchPositionRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSpatialAccessTokenDomain::FFetchPositionTask::FFetchPositionTask(
        const FFetchPositionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSpatialAccessTokenDomain::FFetchPositionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->FetchPosition(
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
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId(),
                        "Spatial"
                    );
                    const auto Key = Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                        Item->GetAreaModelName(),
                        Item->GetLayerModelName()
                    );
                    Self->Cache->Put<Gs2::MegaField::Model::FSpatial>(
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::MegaField::Domain::Model::FSpatialDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetAreaModelName(),
                    (*ResultModel->GetItems())[i]->GetLayerModelName()
                )
            );
            const auto ParentKey = Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                "Spatial"
            );
            const auto Key = Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetAreaModelName(),
                (*ResultModel->GetItems())[i]->GetLayerModelName()
            );
            Self->Cache->Put<Gs2::MegaField::Model::FSpatial>(
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSpatialAccessTokenDomain::FFetchPositionTask>> FSpatialAccessTokenDomain::FetchPosition(
        Request::FFetchPositionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFetchPositionTask>>(this->AsShared(), Request);
    }

    FSpatialAccessTokenDomain::FNearUserIdsTask::FNearUserIdsTask(
        const TSharedPtr<FSpatialAccessTokenDomain> Self,
        const Request::FNearUserIdsRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSpatialAccessTokenDomain::FNearUserIdsTask::FNearUserIdsTask(
        const FNearUserIdsTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSpatialAccessTokenDomain::FNearUserIdsTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->NearUserIds(
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
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::MegaField::Domain::Model::FSpatialAccessTokenDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    Self->AccessToken,
                    Self->AreaModelName,
                    Self->LayerModelName
                )
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSpatialAccessTokenDomain::FNearUserIdsTask>> FSpatialAccessTokenDomain::NearUserIds(
        Request::FNearUserIdsRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FNearUserIdsTask>>(this->AsShared(), Request);
    }

    FSpatialAccessTokenDomain::FActionTask::FActionTask(
        const TSharedPtr<FSpatialAccessTokenDomain> Self,
        const Request::FActionRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSpatialAccessTokenDomain::FActionTask::FActionTask(
        const FActionTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSpatialAccessTokenDomain::FActionTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithAreaModelName(Self->AreaModelName)
            ->WithLayerModelName(Self->LayerModelName);
        const auto Future = Self->Client->Action(
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
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId(),
                        "Spatial"
                    );
                    const auto Key = Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                        Item->GetAreaModelName(),
                        Item->GetLayerModelName()
                    );
                    Self->Cache->Put<Gs2::MegaField::Model::FSpatial>(
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::MegaField::Domain::Model::FSpatialDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::MegaField::Domain::Model::FSpatialDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetAreaModelName(),
                    (*ResultModel->GetItems())[i]->GetLayerModelName()
                )
            );
            const auto ParentKey = Gs2::MegaField::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                "Spatial"
            );
            const auto Key = Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetAreaModelName(),
                (*ResultModel->GetItems())[i]->GetLayerModelName()
            );
            Self->Cache->Put<Gs2::MegaField::Model::FSpatial>(
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSpatialAccessTokenDomain::FActionTask>> FSpatialAccessTokenDomain::Action(
        Request::FActionRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FActionTask>>(this->AsShared(), Request);
    }

    FString FSpatialAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> AreaModelName,
        TOptional<FString> LayerModelName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" +
            (LayerModelName.IsSet() ? *LayerModelName : "null") + ":" +
            ChildType;
    }

    FString FSpatialAccessTokenDomain::CreateCacheKey(
        TOptional<FString> AreaModelName,
        TOptional<FString> LayerModelName
    )
    {
        return FString() +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" + 
            (LayerModelName.IsSet() ? *LayerModelName : "null");
    }

    FSpatialAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FSpatialAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FSpatialAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSpatialAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FSpatial>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::MegaField::Model::FSpatial>(
            Self->ParentKey,
            Gs2::MegaField::Domain::Model::FSpatialDomain::CreateCacheKey(
                Self->AreaModelName,
                Self->LayerModelName
            )
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSpatialAccessTokenDomain::FModelTask>> FSpatialAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSpatialAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

