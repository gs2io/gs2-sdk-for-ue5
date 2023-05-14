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

#include "Formation/Domain/Model/Mold.h"
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

    FMoldDomain::FMoldDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> MoldName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        MoldName(MoldName),
        ParentKey(Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Mold"
        ))
    {
    }

    FMoldDomain::FMoldDomain(
        const FMoldDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FMoldDomain::FGetTask::FGetTask(
        const TSharedPtr<FMoldDomain> Self,
        const Request::FGetMoldByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldName(Self->MoldName);
        const auto Future = Self->Client->GetMoldByUserId(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FGetTask>> FMoldDomain::Get(
        Request::FGetMoldByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FSetCapacityTask::FSetCapacityTask(
        const TSharedPtr<FMoldDomain> Self,
        const Request::FSetMoldCapacityByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FSetCapacityTask::FSetCapacityTask(
        const FSetCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FSetCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldName(Self->MoldName);
        const auto Future = Self->Client->SetMoldCapacityByUserId(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FSetCapacityTask>> FMoldDomain::SetCapacity(
        Request::FSetMoldCapacityByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetCapacityTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FAddCapacityTask::FAddCapacityTask(
        const TSharedPtr<FMoldDomain> Self,
        const Request::FAddMoldCapacityByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FAddCapacityTask::FAddCapacityTask(
        const FAddCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FAddCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldName(Self->MoldName);
        const auto Future = Self->Client->AddMoldCapacityByUserId(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FAddCapacityTask>> FMoldDomain::AddCapacity(
        Request::FAddMoldCapacityByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddCapacityTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMoldDomain> Self,
        const Request::FDeleteMoldByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldName(Self->MoldName);
        const auto Future = Self->Client->DeleteMoldByUserId(
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
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Formation::Model::FMold::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FDeleteTask>> FMoldDomain::Delete(
        Request::FDeleteMoldByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    Gs2::Formation::Domain::Iterator::FDescribeFormsByUserIdIteratorPtr FMoldDomain::Forms(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeFormsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            MoldName,
            UserId
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain> FMoldDomain::Form(
        const int32 Index
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FFormDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            MoldName,
            Index
        );
    }

    FString FMoldDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MoldName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MoldName.IsSet() ? *MoldName : "null") + ":" +
            ChildType;
    }

    FString FMoldDomain::CreateCacheKey(
        TOptional<FString> MoldName
    )
    {
        return FString() +
            (MoldName.IsSet() ? *MoldName : "null");
    }

    FMoldDomain::FModelTask::FModelTask(
        const TSharedPtr<FMoldDomain> Self
    ): Self(Self)
    {

    }

    FMoldDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Formation::Model::FMold>(
            Self->ParentKey,
            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                Self->MoldName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Formation::Request::FGetMoldByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "mold")
                    {
                        Self->Cache->Delete(
                            Gs2::Formation::Model::FMold::TypeName,
                            Self->ParentKey,
                            Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                                Self->MoldName
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
            Value = Self->Cache->Get<Gs2::Formation::Model::FMold>(
                Self->ParentKey,
                Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    Self->MoldName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FModelTask>> FMoldDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMoldDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

