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

#pragma once

#include "CoreMinimal.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Model/Gs2ChatEzMessage.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Chat::Domain::Iterator
{

	class EZGS2_API FEzDescribeLatestMessagesIterator :
        public TSharedFromThis<FEzDescribeLatestMessagesIterator>
    {
        Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIteratorPtr It;
        Gs2::Chat::Domain::Model::FRoomAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;
        TOptional<FString> Password;
        TOptional<int32> Category;

	public:

        explicit FEzDescribeLatestMessagesIterator(
            Gs2::Chat::Domain::Model::FRoomAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            TOptional<FString> Password = TOptional<FString>(),
            TOptional<int32> Category = TOptional<int32>()
        ) :
            It(
                Domain->LatestMessages(
                    Category
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection),
            Password(Password),
            Category(Category)
        {
        }

		FEzDescribeLatestMessagesIterator(
			const FEzDescribeLatestMessagesIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection),
            Password(From.Password),
            Category(From.Category)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeLatestMessagesIterator;

			Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIterator::FIterator DomainIterator;
			Gs2::UE5::Chat::Model::FEzMessagePtr CurrentValue;
        	static Gs2::UE5::Chat::Model::FEzMessagePtr ConvertCurrent(
        		Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Chat::Model::FEzMessage::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeLatestMessagesIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::Chat::Model::FEzMessagePtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzDescribeLatestMessagesIterator> FEzDescribeLatestMessagesIteratorPtr;
}
