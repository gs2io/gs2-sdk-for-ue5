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

#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/Namespace.h"
#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/ProgressAccessToken.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
#include "Quest/Domain/Model/CompletedQuestListAccessToken.h"
#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/User.h"
#include "Quest/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Quest::Domain::Model
{

    FQuestGroupModelMasterDomain::FQuestGroupModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> QuestGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Session)),
        NamespaceName(NamespaceName),
        QuestGroupName(QuestGroupName),
        ParentKey(Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "QuestGroupModelMaster"
        ))
    {
    }

    FQuestGroupModelMasterDomain::FQuestGroupModelMasterDomain(
        const FQuestGroupModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FQuestGroupModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FQuestGroupModelMasterDomain> Self,
        const Request::FGetQuestGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->GetQuestGroupModelMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "QuestGroupModelMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FQuestGroupModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FGetTask>> FQuestGroupModelMasterDomain::Get(
        Request::FGetQuestGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FQuestGroupModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FQuestGroupModelMasterDomain> Self,
        const Request::FUpdateQuestGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->UpdateQuestGroupModelMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "QuestGroupModelMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FQuestGroupModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FUpdateTask>> FQuestGroupModelMasterDomain::Update(
        Request::FUpdateQuestGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FQuestGroupModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FQuestGroupModelMasterDomain> Self,
        const Request::FDeleteQuestGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->DeleteQuestGroupModelMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "QuestGroupModelMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Quest::Model::FQuestGroupModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FDeleteTask>> FQuestGroupModelMasterDomain::Delete(
        Request::FDeleteQuestGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FQuestGroupModelMasterDomain::FCreateQuestModelMasterTask::FCreateQuestModelMasterTask(
        const TSharedPtr<FQuestGroupModelMasterDomain> Self,
        const Request::FCreateQuestModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FQuestGroupModelMasterDomain::FCreateQuestModelMasterTask::FCreateQuestModelMasterTask(
        const FCreateQuestModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FCreateQuestModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithQuestGroupName(Self->QuestGroupName);
        const auto Future = Self->Client->CreateQuestModelMaster(
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
                const auto ParentKey = Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->QuestGroupName,
                    "QuestModelMaster"
                );
                const auto Key = Gs2::Quest::Domain::Model::FQuestModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FQuestModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetQuestGroupName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FCreateQuestModelMasterTask>> FQuestGroupModelMasterDomain::CreateQuestModelMaster(
        Request::FCreateQuestModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateQuestModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Quest::Domain::Iterator::FDescribeQuestModelMastersIteratorPtr FQuestGroupModelMasterDomain::QuestModelMasters(
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Iterator::FDescribeQuestModelMastersIterator>(
            Cache,
            Client,
            NamespaceName,
            QuestGroupName
        );
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FQuestModelMasterDomain> FQuestGroupModelMasterDomain::QuestModelMaster(
        const FString QuestName
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Model::FQuestModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            QuestGroupName,
            QuestName
        );
    }

    FString FQuestGroupModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> QuestGroupName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null") + ":" +
            ChildType;
    }

    FString FQuestGroupModelMasterDomain::CreateCacheKey(
        TOptional<FString> QuestGroupName
    )
    {
        return FString() +
            (QuestGroupName.IsSet() ? *QuestGroupName : "null");
    }

    FQuestGroupModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FQuestGroupModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FQuestGroupModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FQuestGroupModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Model::FQuestGroupModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Quest::Model::FQuestGroupModelMaster> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Quest::Model::FQuestGroupModelMaster>(
            Self->ParentKey,
            Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheKey(
                Self->QuestGroupName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Quest::Request::FGetQuestGroupModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheKey(
                    Self->QuestGroupName
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FQuestGroupModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "questGroupModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Quest::Model::FQuestGroupModelMaster>(
                Self->ParentKey,
                Gs2::Quest::Domain::Model::FQuestGroupModelMasterDomain::CreateCacheKey(
                    Self->QuestGroupName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FQuestGroupModelMasterDomain::FModelTask>> FQuestGroupModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FQuestGroupModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

