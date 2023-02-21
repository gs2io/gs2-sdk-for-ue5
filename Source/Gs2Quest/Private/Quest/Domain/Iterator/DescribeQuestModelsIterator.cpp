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

// ReSharper disable CppUnusedIncludeDirective

#include "Quest/Domain/Iterator/DescribeQuestModelsIterator.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/QuestGroupModel.h"

namespace Gs2::Quest::Domain::Iterator
{

    Gs2::Core::Model::FGs2ErrorPtr FDescribeQuestModelsIteratorLoadTask::Action(
        TSharedPtr<TSharedPtr<TArray<Gs2::Quest::Model::FQuestModelPtr>>> Result)
    {
        const auto Future = Self->Client->DescribeQuestModels(
            MakeShared<Gs2::Quest::Request::FDescribeQuestModelsRequest>()
                ->WithNamespaceName(Self->NamespaceName)
                ->WithQuestGroupName(Self->QuestGroupName)
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto R = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = R->GetItems();
        Self->Last = true;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDescribeQuestModelsIteratorLoadTask>>
    FDescribeQuestModelsIterator::Load()
    {
        return Gs2::Core::Util::New<FAsyncTask<FDescribeQuestModelsIteratorLoadTask>>(SharedThis(this));
    }

    FDescribeQuestModelsIterator::FDescribeQuestModelsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Quest::FGs2QuestRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> QuestGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        QuestGroupName(QuestGroupName),
        FetchSize(TOptional<int32>())
    {

    }
    const Gs2::Quest::Model::FQuestModelPtr& FDescribeQuestModelsIterator::IteratorImpl::operator*() const
    {
        return Current;
    }
    Gs2::Quest::Model::FQuestModelPtr FDescribeQuestModelsIterator::IteratorImpl::operator->()
    {
        return Current;
    }

    FDescribeQuestModelsIterator::IteratorImpl& FDescribeQuestModelsIterator::IteratorImpl::operator++()
    {
        Task->StartSynchronousTask();
        Current = nullptr;
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return *this;
    }

    FDescribeQuestModelsIterator::IteratorImpl FDescribeQuestModelsIterator::begin()
    {
        const auto Task = Next();
        IteratorImpl Impl(Task);
        Task->StartSynchronousTask();
        if (!Task->GetTask().IsError() && Task->GetTask().Result() != nullptr)
        {
            Impl.Current = Task->GetTask().Result();
        }
        Task->EnsureCompletion();
        return Impl;
    }

    // ReSharper disable once CppMemberFunctionMayBeStatic
    FDescribeQuestModelsIterator::IteratorImpl FDescribeQuestModelsIterator::end()
    {
        return IteratorImpl(nullptr);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

