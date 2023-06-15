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

#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FMoldModelMasterDomain::FMoldModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MoldName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        NamespaceName(NamespaceName),
        MoldName(MoldName),
        ParentKey(Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "MoldModelMaster"
        ))
    {
    }

    FMoldModelMasterDomain::FMoldModelMasterDomain(
        const FMoldModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FMoldModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FMoldModelMasterDomain> Self,
        const Request::FGetMoldModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMoldModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMoldName(Self->MoldName);
        const auto Future = Self->Client->GetMoldModelMaster(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModelMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FMoldModelMasterDomain::FGetTask>> FMoldModelMasterDomain::Get(
        Request::FGetMoldModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMoldModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FMoldModelMasterDomain> Self,
        const Request::FUpdateMoldModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMoldName(Self->MoldName);
        const auto Future = Self->Client->UpdateMoldModelMaster(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModelMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FMoldModelMasterDomain::FUpdateTask>> FMoldModelMasterDomain::Update(
        Request::FUpdateMoldModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FMoldModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMoldModelMasterDomain> Self,
        const Request::FDeleteMoldModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMoldName(Self->MoldName);
        const auto Future = Self->Client->DeleteMoldModelMaster(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModelMaster"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Formation::Model::FMoldModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldModelMasterDomain::FDeleteTask>> FMoldModelMasterDomain::Delete(
        Request::FDeleteMoldModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMoldModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MoldName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MoldName.IsSet() ? *MoldName : "null") + ":" +
            ChildType;
    }

    FString FMoldModelMasterDomain::CreateCacheKey(
        TOptional<FString> MoldName
    )
    {
        return FString() +
            (MoldName.IsSet() ? *MoldName : "null");
    }

    FMoldModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FMoldModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FMoldModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMoldModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Formation::Model::FMoldModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Formation::Model::FMoldModelMaster>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FMoldModelMasterDomain::CreateCacheKey(
                Self->MoldName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetMoldModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Formation::Domain::Model::FMoldModelMasterDomain::CreateCacheKey(
                    Self->MoldName
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "moldModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Formation::Model::FMoldModelMaster>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FMoldModelMasterDomain::CreateCacheKey(
                    Self->MoldName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldModelMasterDomain::FModelTask>> FMoldModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMoldModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

