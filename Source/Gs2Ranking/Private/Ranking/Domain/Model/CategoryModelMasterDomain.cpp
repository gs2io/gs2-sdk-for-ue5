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

#include "Ranking/Domain/Model/CategoryModelMaster.h"
#include "Ranking/Domain/Model/Namespace.h"
#include "Ranking/Domain/Model/CategoryModel.h"
#include "Ranking/Domain/Model/CategoryModelMaster.h"
#include "Ranking/Domain/Model/Subscribe.h"
#include "Ranking/Domain/Model/SubscribeAccessToken.h"
#include "Ranking/Domain/Model/Score.h"
#include "Ranking/Domain/Model/ScoreAccessToken.h"
#include "Ranking/Domain/Model/Ranking.h"
#include "Ranking/Domain/Model/RankingAccessToken.h"
#include "Ranking/Domain/Model/CurrentRankingMaster.h"
#include "Ranking/Domain/Model/SubscribeUser.h"
#include "Ranking/Domain/Model/SubscribeUserAccessToken.h"
#include "Ranking/Domain/Model/User.h"
#include "Ranking/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Ranking::Domain::Model
{

    FCategoryModelMasterDomain::FCategoryModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> CategoryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Ranking::FGs2RankingRestClient>(Session)),
        NamespaceName(NamespaceName),
        CategoryName(CategoryName),
        ParentKey(Gs2::Ranking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CategoryModelMaster"
        ))
    {
    }

    FCategoryModelMasterDomain::FCategoryModelMasterDomain(
        const FCategoryModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        CategoryName(From.CategoryName),
        ParentKey(From.ParentKey)
    {

    }

    FCategoryModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FCategoryModelMasterDomain> Self,
        const Request::FGetCategoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCategoryModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FCategoryModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->GetCategoryModelMaster(
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
                const auto ParentKey = Gs2::Ranking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CategoryModelMaster"
                );
                const auto Key = Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Ranking::Model::FCategoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCategoryModelMasterDomain::FGetTask>> FCategoryModelMasterDomain::Get(
        Request::FGetCategoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCategoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCategoryModelMasterDomain> Self,
        const Request::FUpdateCategoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCategoryModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->UpdateCategoryModelMaster(
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
                const auto ParentKey = Gs2::Ranking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CategoryModelMaster"
                );
                const auto Key = Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Ranking::Model::FCategoryModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FCategoryModelMasterDomain::FUpdateTask>> FCategoryModelMasterDomain::Update(
        Request::FUpdateCategoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCategoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FCategoryModelMasterDomain> Self,
        const Request::FDeleteCategoryModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCategoryModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithCategoryName(Self->CategoryName);
        const auto Future = Self->Client->DeleteCategoryModelMaster(
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
                const auto ParentKey = Gs2::Ranking::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CategoryModelMaster"
                );
                const auto Key = Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Ranking::Model::FCategoryModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCategoryModelMasterDomain::FDeleteTask>> FCategoryModelMasterDomain::Delete(
        Request::FDeleteCategoryModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FCategoryModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> CategoryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (CategoryName.IsSet() ? *CategoryName : "null") + ":" +
            ChildType;
    }

    FString FCategoryModelMasterDomain::CreateCacheKey(
        TOptional<FString> CategoryName
    )
    {
        return FString("") +
            (CategoryName.IsSet() ? *CategoryName : "null");
    }

    FCategoryModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FCategoryModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FCategoryModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCategoryModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Ranking::Model::FCategoryModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Ranking::Model::FCategoryModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Ranking::Model::FCategoryModelMaster>(
            Self->ParentKey,
            Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                Self->CategoryName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Ranking::Request::FGetCategoryModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    Self->CategoryName
                );
                Self->Cache->Put(
                    Gs2::Ranking::Model::FCategoryModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "categoryModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Ranking::Model::FCategoryModelMaster>(
                Self->ParentKey,
                Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
                    Self->CategoryName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCategoryModelMasterDomain::FModelTask>> FCategoryModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCategoryModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FCategoryModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Ranking::Model::FCategoryModelMasterPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::Ranking::Model::FCategoryModelMaster::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
            CategoryName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Ranking::Model::FCategoryModelMaster>(obj));
            }
        );
    }

    void FCategoryModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::Ranking::Model::FCategoryModelMaster::TypeName,
            ParentKey,
            Gs2::Ranking::Domain::Model::FCategoryModelMasterDomain::CreateCacheKey(
            CategoryName
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

